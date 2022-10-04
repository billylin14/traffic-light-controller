// Task2.c functions

/*
 * Student name:        Billy Lin
 * Student ID:          1765327
 * Date:                05.28.2020
 *
 * EE474/Lab4/lab4_task2a.c:
 * This C file includes the functions that are used in EE474 lab 4 task 2.
 */

#include <stdint.h>
#include <stdio.h>
#include "myheader.h"
#include "Lab_3_Header.h"
#include "Lab_3_Driver.h"
#include "tm4c1294ncpdt.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"


/*Variable Declarations................................*/

extern int counter;
extern unsigned int start_counter;
extern unsigned int ped_counter;
extern unsigned char start_on;
extern unsigned char ped_on;

//switches position
int onoff_x = 40;
int onoff_y = 190;
int ped_x = 280;
int ped_y = 190;
int onoff_r = 25;
int ped_r = 25;
//coordinate of virtual traffic light
int light_x = 40;
int light_y = 50;

/*Function Declarations................................*/
//create the traffic lights and initialize in all off states
void makeLights();

//create 2 buttons and print each's functionality below the buttons on LCD panel
void makeTrafficLightButtons();

//turn all the lights off
void lightsOff();

//turn only green light on
void greenOn();

//turn only yellow light on
void yellowOn();

//turn only red light on
void redOn();

//setup LCD panel
void LCD_setup();

//determine if the user has valid presses on the buttons 
//return a char with 2 bit value: LSB=SW2 pressed, second bit=SW1 pressed
char validPress();

//implement the fsm of the traffic lights with LCD
void fsm_LCD();

//main program of lab4 task2a
//hooks every functionality up in a program
//place this method call in main.c to run task2a.
void trafficLight_LCD();

/*...................................TASK_2_MODULES............................................*/

//create 2 buttons and print each's functionality below the buttons on LCD panel
void makeTrafficLightButtons() {
  //                   x        y               radius        color
  LCD_DrawFilledCircle(onoff_x, onoff_y,        onoff_r,      Color4[14]); //SW1 (bright yellow)
  LCD_DrawFilledCircle(ped_x,   ped_y,          ped_r,        Color4[10]); //SW2  (bright green)
  LCD_SetCursor(onoff_x, onoff_y+25);
  LCD_PrintString("Ped");
  LCD_SetCursor(ped_x, ped_y+25);
  LCD_PrintString("Reset");
}

//create the traffic lights and initialize in all off states
void makeLights() {
  //                   x        y               width             height            color
  LCD_DrawFilledRect  (light_x, light_y,        ped_x-onoff_x,    onoff_r*2+20,     Color4[7]); //background  (light grey)
  
  //                   x                        y                       radius        color
  LCD_DrawFilledCircle(light_x+onoff_r+15,      light_y+onoff_r+10,     onoff_r,      Color4[2]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+onoff_r+95,      light_y+onoff_r+10,     onoff_r,      Color4[6]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+onoff_r+175,     light_y+onoff_r+10,     onoff_r,      Color4[4]); //red lgiht          off (red 4)     on (bright red 12)
}

//turn all the lights off
void lightsOff() {
  LCD_DrawFilledCircle(light_x+onoff_r+15,        light_y+onoff_r+10,       onoff_r,        Color4[2]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+onoff_r+95,        light_y+onoff_r+10,       onoff_r,        Color4[6]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+onoff_r+175,       light_y+onoff_r+10,       onoff_r,        Color4[4]); //red lgiht          off (red 4)     on (bright red 12)
}

//turn only green light on
void greenOn() {
  LCD_DrawFilledCircle(light_x+onoff_r+15,        light_y+onoff_r+10,       onoff_r,        Color4[10]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+onoff_r+95,        light_y+onoff_r+10,       onoff_r,        Color4[6]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+onoff_r+175,       light_y+onoff_r+10,       onoff_r,        Color4[4]); //red lgiht          off (red 4)     on (bright red 12)
}

//turn only yellow light on
void yellowOn() {
  LCD_DrawFilledCircle(light_x+onoff_r+15,        light_y+onoff_r+10,       onoff_r,        Color4[2]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+onoff_r+95,        light_y+onoff_r+10,       onoff_r,        Color4[14]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+onoff_r+175,       light_y+onoff_r+10,       onoff_r,        Color4[4]); //red lgiht          off (red 4)     on (bright red 12)
}

//turn only red light on
void redOn() {
  LCD_DrawFilledCircle(light_x+onoff_r+15,        light_y+onoff_r+10,       onoff_r,        Color4[2]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+onoff_r+95,        light_y+onoff_r+10,       onoff_r,        Color4[6]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+onoff_r+175,       light_y+onoff_r+10,       onoff_r,        Color4[12]); //red lgiht          off (red 4)     on (bright red 12)
}

//setup LCD panel
void LCD_setup(){
  //LCD setup
  LCD_Init();
  LCD_ColorFill(Color4[9]);
  //LCD touch init
  Touch_Init();
  //make button and led lights
  makeTrafficLightButtons();
  makeLights();
}

//determine if the user has valid presses on the buttons 
char validPress() {
  //touch detection
  volatile unsigned long x = Touch_ReadX();
  volatile unsigned long y = Touch_ReadY();
//  printf("touch x %d\n", (int)x);
//  printf("touch y %d\n\n", (int)y);
  //valid onoff press range
  volatile unsigned char in_onoff_x = ((x > 500) && (x < 1200));
  volatile unsigned char in_onoff_y = ((y > 500) && (y < 1000));
  //valid ped press range
  volatile unsigned char in_ped_x = (x > 1800) && (x < 3000);
  volatile unsigned char in_ped_y = (y > 500) && (y < 1000);
  //valid press?
  volatile unsigned char valid_onoff = (in_onoff_x && in_onoff_y)<<1;
  volatile unsigned char valid_ped = in_ped_x && in_ped_y;
  return valid_onoff | valid_ped;
}

//implement the fsm of the traffic lights with LCD
void fsm_LCD() {
  //FSM structures
  typedef enum{idle, go, warn, stop} state;
  state ps = idle;
  
  //state transition
  while(1){
    //traffic light
    switch(ps) {
      case idle:
        //LED on/off decision
        lightsOff();
        //state transition logic
        if ((validPress()&0x1)){ //if onoff button is pressed
          if (start_counter >= 2) {
            start_counter = 0;
            ped_counter = 0;
            counter = 0;
            ps = stop;
          }
        } else {
          start_counter = 0;
          ped_counter = 0;
        }  
        break;
      case go:
        //LEDs on/off decision
        greenOn();
        //state transition logic
        if (validPress()&0x1){
          if (start_counter >= 2) {
            start_counter = 0;
            ped_counter = 0;
            counter = 0;
            ps = idle;
          } 
        } else {
          start_counter = 0;
        }
        if (((validPress()&0x2)>>1)==1){
          if (ped_counter >= 2) {
            start_counter = 0;
            ped_counter = 0;
            counter = 0;
            ps = warn;
          }
        } else {
          ped_counter = 0;
        }
        if (counter >= 5){
          start_counter = 0;
          ped_counter = 0;
          counter = 0;
          ps = stop;
        }
        break;
      case warn:
        //LEDs on/off decision
        yellowOn();
        //state transition logic
        if (validPress()&0x1){
          if (start_counter >= 2) {
            start_counter = 0;
            ped_counter = 0;
            counter = 0;
            ps = idle;
          } 
        } else {
          start_counter = 0;
        }
        if (counter >= 5){
          start_counter = 0;
          ped_counter = 0;
          counter = 0;
          ps = stop;
        }
        break;
      case stop:
        //LEDs on/off decision
        redOn();
        //state transition logic
        if (validPress()&0x1){
          if (start_counter >= 2) {
            start_counter = 0;
            ped_counter = 0;
            counter = 0;
            ps = idle;
          } 
        } else {
          start_counter = 0;
        }
        if (counter >= 5){
          start_counter = 0;
          ped_counter = 0;
          counter = 0;
          ps = go;
        }
        
        break;
    }
  }
}

//main program that hooks each module up.
void trafficLight_LCD(){
  //timer initializations
  timer_init();
  timer_interrupt_init();
  timer_interrupt_set();
  //lcd setup
  LCD_setup();
  //fsm
  fsm_LCD();
}
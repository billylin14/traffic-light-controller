// Task2.c functions

/*
 * Student name:        Billy Lin
 * Student ID:          lin14
 * Date:                05.24.2020
 *
 * EE474/Lab4/lab4_task2b.c:
 * This C file includes the functions that are used in EE474 lab 4 task 2b.
 */

#include <stdint.h>
#include <stdio.h>
//#include "myheader.h"
//#include "Lab_3_Header.h"
//#include "Lab_3_Driver.h"
#include "tm4c1294ncpdt.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"


/*Variable Declarations................................*/

//switches position
int sw1_x = 40;
int sw1_y = 190;
int sw2_x = 280;
int sw2_y = 190;
int sw1_r = 25;
int sw2_r = 25;
//coordinate of virtual traffic light
int light_x = 40;
int light_y = 50;

/*Function Declarations................................*/

//makes the onoff/ped buttons and print their names below the buttons
void makeButtons();

//makes the traffic lights: a grey frame with three oval lights (green, yellow, red)
void makeLights();

//turn all the lights off
void lightsOff();

//turn only green light on
void greenOn();

//turn only yellow light on
void yellowOn();

//turn only red light on
void redOn();

//determine if the user has valid presses on the buttons 
//return a char with 2 bit value: LSB=SW2 pressed, second bit=SW1 pressed
char validPress();


/*...................................TASK_2_MODULES............................................*/

void makeButtons() {
  //                   x          y       radius        color
  LCD_DrawFilledCircle(sw1_x,     sw1_y,  sw1_r,        Color4[14]); //SW1 (bright yellow)
  LCD_DrawFilledCircle(sw2_x,     sw2_y,  sw2_r,        Color4[10]); //SW2  (bright green)
  LCD_SetCursor(sw1_x, sw1_y+25);
  LCD_PrintString("Ped");
  LCD_SetCursor(sw2_x, sw2_y+25);
  LCD_PrintString("Reset");
}

void makeLights() {
  //                   x        y               width           height          color
  LCD_DrawFilledRect  (light_x, light_y,        sw2_x-sw1_x,    sw1_r*2+20,     Color4[7]); //background  (light grey)
  
  //                   x                        y                       radius        color
  LCD_DrawFilledCircle(light_x+sw1_r+15,        light_y+sw1_r+10,       sw1_r,        Color4[2]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+sw1_r+95,        light_y+sw1_r+10,       sw1_r,        Color4[6]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+sw1_r+175,       light_y+sw1_r+10,       sw1_r,        Color4[4]); //red lgiht          off (red 4)     on (bright red 12)
}

void lightsOff() {
  LCD_DrawFilledCircle(light_x+sw1_r+15,        light_y+sw1_r+10,       sw1_r,        Color4[2]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+sw1_r+95,        light_y+sw1_r+10,       sw1_r,        Color4[6]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+sw1_r+175,       light_y+sw1_r+10,       sw1_r,        Color4[4]); //red lgiht          off (red 4)     on (bright red 12)
}

void greenOn() {
  LCD_DrawFilledCircle(light_x+sw1_r+15,        light_y+sw1_r+10,       sw1_r,        Color4[10]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+sw1_r+95,        light_y+sw1_r+10,       sw1_r,        Color4[6]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+sw1_r+175,       light_y+sw1_r+10,       sw1_r,        Color4[4]); //red lgiht          off (red 4)     on (bright red 12)
}

void yellowOn() {
  LCD_DrawFilledCircle(light_x+sw1_r+15,        light_y+sw1_r+10,       sw1_r,        Color4[2]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+sw1_r+95,        light_y+sw1_r+10,       sw1_r,        Color4[14]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+sw1_r+175,       light_y+sw1_r+10,       sw1_r,        Color4[4]); //red lgiht          off (red 4)     on (bright red 12)
}

void redOn() {
  LCD_DrawFilledCircle(light_x+sw1_r+15,        light_y+sw1_r+10,       sw1_r,        Color4[2]); //green light        off (green 2)   on (bright green 10)
  LCD_DrawFilledCircle(light_x+sw1_r+95,        light_y+sw1_r+10,       sw1_r,        Color4[6]); //yellow light       off (yellow 6)  on (bright yellow 14)
  LCD_DrawFilledCircle(light_x+sw1_r+175,       light_y+sw1_r+10,       sw1_r,        Color4[12]); //red lgiht          off (red 4)     on (bright red 12)
}

char validPress() {
  //touch detection
  volatile unsigned long x = Touch_ReadX();
  volatile unsigned long y = Touch_ReadY();
//  printf("touch x %d\n", (int)x);
//  printf("touch y %d\n\n", (int)y);
  //valid sw1 press range
  volatile unsigned char in_sw1_x = ((x > 500) && (x < 1200));
  volatile unsigned char in_sw1_y = ((y > 500) && (y < 1000));
  //valid sw2 press range
  volatile unsigned char in_sw2_x = (x > 1800) && (x < 3000);
  volatile unsigned char in_sw2_y = (y > 500) && (y < 1000);
  //valid press?
  volatile unsigned char valid_sw1 = (in_sw1_x && in_sw1_y)<<1;
  volatile unsigned char valid_sw2 = in_sw2_x && in_sw2_y;
  return valid_sw1 | valid_sw2;
}

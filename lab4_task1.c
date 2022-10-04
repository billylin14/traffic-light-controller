// Task1.c functions

/*
 * Student name:        Billy Lin
 * Student ID:          1765327
 * Date:                05.21.2020
 *
 * EE474/Lab4/lab4_task1.c:
 * This C file includes the functions that are used in EE474 lab 4 task 1.
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
extern int counter1;
extern double temperature;
extern enum frequency freq;

int sw1_x = 0;
int sw1_y = 190;
int sw2_x = 245;
int sw2_y = 190;
int sw1_width = 75;
int sw1_height = 50;
int sw2_width = 75;
int sw2_height = 50;

/*Function Declarations................................*/
//takes the temperature value from ADC
//prints the value in Celsius and Fahrenheit and the current clock frequency
void printTemperature();

//draws two retangular buttons and prints the name of the buttons
void makeButtons();

//reads the coordinate values returned by the touch screen
//determines if the coordinates lie within the range of either button
//and changes the clock to the corresponding frequency
void readTouch();

//main program of lab4 task1
//hooks every functionality up in a program
//place this method call in main.c to run task1.
void tempReadingOnLCD();

/*...................................TASK_1_MODULES............................................*/

//TASK1 MODULEs: 
void printTemperature() {  
  double tempC = temperature;
  double tempF = temperature*9/5 + 32;
  printf("%.2f, %.2f\n", tempC, tempF);
  printf("%d\n\n", freq);
  LCD_Goto(0,0);
  LCD_Printf("The current temperature is ");
  LCD_PrintFloat(tempC);
  LCD_PrintString(" C, ");
  LCD_PrintFloat(tempF);
  LCD_PrintString(" F.");
  LCD_PrintChar('\n');
  LCD_Printf("The current clock frequency is %d MHz.", freq);
  LCD_Goto(0,0); //keep the printing at the top.
}

void makeButtons() {
  //                 x          y       width           height          color
  LCD_DrawFilledRect(sw1_x,     sw1_y,  sw1_width,      sw1_height,     Color4[14]); //SW1 (bright yellow)
  LCD_DrawFilledRect(sw2_x,     sw2_y,  sw2_width,      sw2_height,     Color4[10]); //SW2  (bright green)
  LCD_SetCursor(sw1_x, sw1_y+25);
  LCD_PrintString("SW1: 120MHz");
  LCD_SetCursor(sw2_x, sw2_y+25);
  LCD_PrintString("SW2: 12MHz");
}

void readTouch() {
  //touch detection
  unsigned long x = Touch_ReadX();
  unsigned long y = Touch_ReadY();
  printf("touch x %ld\n", x);
  printf("touch y %ld\n\n", y);
  //valid press identification
  int in_sw1_x = (x > 500) && (x < 1200);
  int in_sw1_y = (y > 500) && (y < 1000);
  int in_sw2_x = (x > 1800) && (x < 3000);
  int in_sw2_y = (y > 500) && (y < 1000);
  printf("in sw 1 x = %d\n", in_sw1_x);
  printf("in sw 1 y = %d\n\n", in_sw1_y);
  printf("in sw 2 x = %d\n", in_sw2_x);
  printf("in sw 2 y = %d\n\n", in_sw2_y);
  //button actions
  if (in_sw1_x && in_sw1_y) { //valid press at sw1
    freq = PRESET3;    //switch to lowest freq 12 Mhz
    PLL_Init(freq);
    //change timer countdown
    GPTMTAILR_TIMER0 = 12000000; //to achieve 1 Hz rate
    GPTMTAILR_TIMER1 = 6000000; //to achieve 2 Hz rate
  } else if (in_sw2_x && in_sw2_y) { //valid press at sw2
    freq = PRESET1;  //switch to highest freq 120 Mhz
    PLL_Init(freq);
    GPTMTAILR_TIMER0 = 120000000; //to achieve 1 Hz rate
    GPTMTAILR_TIMER1 = 60000000; //to achieve 2 Hz rate
  } 
}

void tempReadingOnLCD() {
  freq = PRESET2;
  PLL_Init(freq);             // PLL must be configured before everthing else
  timers_init();
  //adc0 setup
  adc0_init();
  adc0_interrupt_setup();
  
  //internal_sw setup
  int_switch_init();
  GPIO_J_interrupt_init();
  GPIO_J_interrupt_set();
  
  //LCD setup
  LCD_Init();
  LCD_ColorFill(Color4[9]);
  
  //LCD touch init
  Touch_Init();
  
  //make button
  makeButtons();
  
  while (1){
    printTemperature();
    readTouch();
  }
}
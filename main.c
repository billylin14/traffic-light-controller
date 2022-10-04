/*
 * Student name:        Billy Lin
 * Student ID:          lin14
 * Date:                05.30.2020
 *
 * EE474/Lab4/main.c:
 * This file incorporates a header file that defines registers, macros, and system functions 
 * and some other .C files that define functions, including setup modules and task modules.
 * The main program picks a task module to run.
 */


#include <stdint.h>
#include "myheader.h"
#include "Lab_3_Header.h"
#include "Lab_3_Driver.h"
#include "tm4c1294ncpdt.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"

/*Variable Declarations................................*/
extern int counter0;
extern int counter1;
extern enum frequency freq;
extern double temperature;
extern enum frequency freq;
extern const unsigned short Color4[16];

int main(void)
{
  tempReadingOnLCD();
  //trafficLight_LCD();
  return 0;
}

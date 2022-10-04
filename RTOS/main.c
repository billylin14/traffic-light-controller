// This is the starter code for the Lab 4 Task 2B.
// Designed for ECE/CSE 474 Spring 20.
//
// Please read through the entire file and make sure
// you understand your tasks, the structure of the code,
// and the hints you are given (although you are not
// required to follow them)
//
// The only requirement is to use the three tasks specified
// in the main function. Feel free to add/delete the code we
// provided, though it is recommended to follow the hints.
//
// Here's the documentation page for FreeRTOS.
// You may want to look at it when doing this assignment.
// https://www.freertos.org/FreeRTOS-quick-start-guide.html

#include <stdio.h>
#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "myheader.h"
#include "tm4c1294ncpdt.h"
#include "SSD2119_Display.h"
#include "SSD2119_Touch.h"
// Include the LCD driver's header file and your own header file here.

// After skimming through the entire file,
// you might want to add some FSM states here.


// Hint:
//
// The following global variables are flags you may want to use
volatile int pedestrian_status = 0;
volatile int onoff_status = 0;

// states declaration
typedef enum{idle, go, warn, stop} state;
volatile state ps = idle;
// state transition flags for FSM
volatile int next_on = 0;


// Below are function prototypes for our RTOS task.
// You should not change the function declerations.
// However, you are allowed to add more helper functions
// as needed.

// Task function that checks the state of the virtual pedestrian button.
// Keeps track of how many seconds the pedestrian button has been pressed.
// Once the user has pressed the virtual pedestrian button for 2 seconds,
// it will set the global flag indicating the virtual pedestrian button
// has been pressed.
void Pedestrian(void *p);

// Task function that checks the state of the virtual onoff button.
// Keeps track of how many seconds the onoff button has been pressed.
// Once the user has pressed the onoff button for 2 seconds,
// it will set the global flag indicating the onoff button has been
// pressed
void StartStop(void *p);

// Task function that represents your Finite State Machine.
// Keeps track of how many seconds the virtual traffic light has been
// lighting on. It will update the state of the traffic light system
// every 5 seconds or once there's virtual button input.
void Control(void *p);

// Helper function that represents your FSM.
// You are allowed to change this function decleration.
//
// Handles the traffic light state transition.
void FSM(void);

//clear all state flags for the next state
void clearStateFlags();


// Do not modify this function.
//
// This hook is called by FreeRTOS when an stack overflow error is detected.
void vApplicationStackOverflowHook(xTaskHandle *pxTask, char *pcTaskName) {
  // This function can not return, so loop forever.  Interrupts are disabled
  // on entry to this function, so no processor interrupts will interrupt
  // this loop.
  while (1) {}
}


// Initialize FreeRTOS and start the tasks.
int main(void) {
  // STEP 1
  //
  // This is the beginning of the main function,
  // Initialize your system by initialize the display and touch
  // functionalities of your SSD2119 touch display assembly. You may
  // also want to initialize (draw) your virtual buttons here.
  
 //LCD setup
  LCD_Init();
  LCD_ColorFill(Color4[9]);
  
  //LCD touch init
  Touch_Init();
 
  //make button and led lights
  makeButtons();
  makeLights();
  
  // STEP 2
  //
  // The code below creates three tasks.
  // Your task here is to assign priorities to the tasks.
  //
  // Think about which task(s) should be given the highest
  // priority and which should be given lower. It is possible to assign
  // the same priority to all the tasks, however.
  //
  // Priorities are in range: [0, configMAX_PRIORITIES - 1], where
  // configMAX_PRIORITIES - 1 corresponds to the highest priority and
  // 0 corresponds to the lowest priority.
  // You can find configMAX_PRIORITIES defined in the file called FreeRTOSConfig.h
  // under the freertos_demo directory.
  //
  // You should not create more tasks. However, you are allowed to add as many
  // helper functions as you want.
  // xTaskCreate(Function Name,
  //             Descriptive Task Name,
  //             Stack Depth,
  //             Task Function Parameter,
  //             Priority,
  //             Task Handle);
  xTaskCreate(StartStop, (const char *)"StartStopButton", 1024, NULL, 8, NULL);         //start/stop system is the second highest priority
  xTaskCreate(Pedestrian, (const char *)"PedestrianButton", 1024, NULL, 8, NULL);       //ped is the lowest priority
  xTaskCreate(Control, (const char *)"Control FSM", 1024, NULL, 10, NULL);               //control is the highest priority

  // Start the scheduler. This should not return.
  // The scheduler will do the scheduling and switch between
  // different tasks for you.
  // Refer to the lecture slides and RTOS documentation
  // page for more details about task scheduling and context switching.
  //
  // One important concept for context switching and task scheduling
  // is preemption. Think about what the terminology preemptive and
  // non-preemptive mean.
  //
  // Hint: Non-preemptive scheduling will allow other tasks to be scheduled
  // after the current task has entered the "waiting state". That is, in our context,
  // the current task will keep running until it reaches vTaskDelay
  // (you'll see this in task functions).
  //
  // You can find in FreeRTOSConfig.h the setting of preemption
  // for the RTOS. Feel free to change this setting as needed.
  vTaskStartScheduler();

  // In case the scheduler returns for some reason, loop forever.
  while(1) {}

}

void StartStop(void *p) {                                                       //enter when onoff button is pressed
  // Hint:
  //
  // Static variable will only be decleared once and
  // will retain its last assigned value until the entire
  // program exits
  static int curr_onoff_tick_time = 0;
  static int prev_onoff_tick_time = 0;                                          

  // xTaskGetTickCount() will return the count of ticks
  // since the Task Scheduler started (i.e. your program starts executing).
  //
  // The tick rate (configTICK_RATE_HZ) is defined in FreeRTOSConfig.h,
  // the default rate is 1000 (1KHz), so one tick is equivalent to 1 ms
  //
  // It is similar to the timer we used before, but you'll
  // need to calculate the time elapsed by taking the difference
  // between curr_tick and prev_tick.
  curr_onoff_tick_time = xTaskGetTickCount();

  // STEP 3
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual StartStop button has been
  // pressed for 2 seconds and needs to set the global flags accordingly
  //
  // Task function should never return so is typically
  // implemented as an infinite loop
  //
  // The vTaskDelay(n) will cause the task to enter Blocked state
  // for n system clock ticks. i.e. the task is unblocked
  // after n systicks and will enter Ready State to be arranged for
  // running
  while (1) {                                                                   //when to return to control task?
    curr_onoff_tick_time = xTaskGetTickCount();                                 //does this method only check for button holding?

    // Check whether the virtual button is pressed.
    //
    // If the virtual button has been pressed for 2 or more seconds,
    // set the global flag to 1 and set the prev_tick to be equal
    // to curr_tick (clear the timer). Otherwise clear the global flag.
    //
    // If the virtual button is not pressed, clear the global flag and
    // set the prev_tick to curr_tick.
    if ((validPress()&0x1)) { // replace this condition checking with something else             //check whether the onoff button is held          
      //printf("detected valid onOff pressed!\n\n");
      if (curr_onoff_tick_time - prev_onoff_tick_time >= 2000) {
        // Set the global flag
        onoff_status = 1;
        // Clear the timer
        curr_onoff_tick_time = prev_onoff_tick_time;
                                                                                
      } else {
        // Clear the global flag
        onoff_status = 0;
      }
    } else {
      // Clear the global flag
      onoff_status = 0;
      // Clear the timer
      curr_onoff_tick_time = prev_onoff_tick_time;
    }

    vTaskDelay(1);
  }
}

void Pedestrian(void *p) {                                                      //when to return to control task?
  //printf("entered pedestrian!\n\n");
  
  static int curr_ped_tick_time = 0;                                            //does this method only check for button holding?
  static int prev_ped_tick_time = 0;

  // STEP 4
  //
  // Complete the implementation of this task function.
  // It checks whether the virtual pedestrian button has been pressed
  // for 2 seconds and update the global flag accordingly.
  //
  // (Refer to instructions in the StartStop function to implement
  // this function.)
  while (1) {
    curr_ped_tick_time = xTaskGetTickCount();

    // Check whether the virtual button is pressed.
    //
    // If the virtual button has been pressed for 2 or more seconds,
    // set the global flag to 1 and set the prev_tick to be equal
    // to curr_tick (clear the timer). Otherwise clear the global flag.
    //
    // If the virtual button is not pressed, clear the global flag and
    // set the prev_tick to curr_tick.
    if (((validPress()&0x2)>>1)==1) { // replace this condition checking with something else             //check onoff button           
      //printf("detected valid ped button pressed!\n\n");
      if (curr_ped_tick_time - prev_ped_tick_time >= 2000) {
        // Set the global flag
        pedestrian_status = 1;
        // Clear the timer
        curr_ped_tick_time = prev_ped_tick_time;
      }
      else {
        // Clear the global flag
        onoff_status = 0;
      }
    } else {
      // Clear the global flag
      onoff_status = 0;
      // Clear the timer
      curr_ped_tick_time = prev_ped_tick_time;
    }
    vTaskDelay(1);
  }
}

void Control(void *p) {                                                         //main command center?
  //printf("entered control!\n\n");
  
  static int curr_light_tick_time = 0;
  static int prev_light_tick_time = 0;

  // STEP 5
  //
  // Complete the implementation of this task function.
  // It represents your Finite State Machine.
  while (1) {
    curr_light_tick_time = xTaskGetTickCount();

    // If the one of the virtual lights been lighting up for 5 or more
    // seconds, or if any of the virtual button flags has been set, switch
    // to the corresponding next state and reset the light tick.
    if (onoff_status) {  // replace this condition checking with something else //if onoff button is pressed
      // Reset the light tick
      prev_light_tick_time = curr_light_tick_time;                                                    //set reset signal                                              
    } else if (pedestrian_status){                                              //if ped button is pressed
      // Reset the light tick
      prev_light_tick_time = curr_light_tick_time;                            //set ped_on                                                   
    } else {                                                                        
      if (curr_light_tick_time - prev_light_tick_time >= 5000) {                //if one light has been lightening up for 5 sec:
        // Reset the light tick
        prev_light_tick_time = curr_light_tick_time;
        next_on = 1;
      }
    }
    FSM();                                                                      
    vTaskDelay(1);
  }
}

void FSM(void) {
  // STEP 6
  //
  // Add your FSM implementation here.
  // This function will be called by the control task function.
  switch(ps) {
    case idle:
      lightsOff();
      if (onoff_status) {
        ps = stop;
        clearStateFlags();
      }
      break;
    case go:
      greenOn();
      if (onoff_status) {
        ps = idle;
        clearStateFlags();
      } else if (pedestrian_status) {
        ps = warn;
        clearStateFlags();
      } else if (next_on) {
        ps = stop;
        clearStateFlags();
      }
      break;
    case warn:
      yellowOn();
      if (onoff_status) {
        ps = idle;
        clearStateFlags();
      } else if (next_on) {
        ps = stop;
        clearStateFlags();
      }
      break;
    case stop:
      redOn();
      if (onoff_status) {
        ps = idle;
        clearStateFlags();
      } else if (next_on) {
        ps = go;
        clearStateFlags();
      }
      break;
  }
}

//clear all state flags for the next state
void clearStateFlags() {
  onoff_status = 0;
  pedestrian_status = 0;
  next_on = 0;
}

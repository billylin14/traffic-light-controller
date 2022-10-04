// My header file

/*
 * Student name:        Billy Lin
 * Student ID:          1765327
 * Date:                05.01.2020
 *
 * myheader.h:
 * This header file includes the registers and define function prototypes and macros.
 */

#ifndef MY_HEADER_H
#define MY_HEADER_H

/*UART Related Registers.................................*/
# define RCGCUART       *((volatile uint32_t *)0x400FE618) //enable and disable the UART modules in Run mode.
# define GPIOPCTL_PORTA *((volatile uint32_t *)0x4005852C) //selects the specific peripheral signal for each GPIO pin when using the alternate function mode
# define UARTIBRD_UART0 *((volatile uint32_t *)0x4000C024) //integer part of the baud-rate divisor value.
# define UARTIBRD_UART2 *((volatile uint32_t *)0x4000E024)
# define UARTFBRD_UART0 *((volatile uint32_t *)0x4000C028) //fractional part of the baud-rate divisor value.
# define UARTFBRD_UART2 *((volatile uint32_t *)0x4000E028)
# define UARTCTL_UART0  *((volatile uint32_t *)0x4000C030) //the control register
# define UARTCTL_UART2  *((volatile uint32_t *)0x4000E030)
# define UARTLCRH_UART0 *((volatile uint32_t *)0x4000C02C) //line control register. Serial parameters such as data length, parity, and stop bit selection are implemented in this register.
# define UARTLCRH_UART2 *((volatile uint32_t *)0x4000E02C) 
# define UARTCC_UART0   *((volatile uint32_t *)0x4000CFC8) //controls the baud clock source for the UART module
# define UARTCC_UART2   *((volatile uint32_t *)0x4000EFC8) 
# define UARTFR_UART0   *((volatile uint32_t *)0x4000C018) //controls the baud clock source for the UART module
# define UARTFR_UART2   *((volatile uint32_t *)0x4000E018)

# define UARTDR_UART0   *((volatile uint32_t *)0x4000C000) //data register
# define UARTDR_UART2   *((volatile uint32_t *)0x4000E000) //data register

# define UARTRIS_UART2  *((volatile uint32_t *)0x4000E03C) //the raw interrupt status register
# define UARTICR_UART2  *((volatile uint32_t *)0x4000E044) //interrupt clear register

/*ADC Related Registers.................................*/

//ADC0 setup
# define RCGCADC        *((volatile uint32_t *)0x400FE638) //enable and disable the ADC modules in Run mode.
# define ADCACTSS_ADC0  *((volatile uint32_t *)0x40038000) //enable the sample sequencer
# define ADCCC_ADC0     *((volatile uint32_t *)0x40038FC8) //controls the clock source for the ADC module
# define ADCEMUX_ADC0   *((volatile uint32_t *)0x40038014) //selects the event (trigger) that initiates sampling for each sample sequencer.
# define ADCSSMUX3_ADC0 *((volatile uint32_t *)0x400380A0) //defines the analog input configuration for each sample in a sequence executed with Sample Sequencer 3
# define ADCSSCTL3_ADC0 *((volatile uint32_t *)0x400380A4) //contains the configuration information for a sample executed with Sample Sequencer 
# define ADCPSSI_ADC0   *((volatile uint32_t *)0x40038028) //provides a mechanism for application software to initiate sampling in the sample sequencers
# define ADCSSFIFO3_ADC0 *((volatile uint32_t *)0x400380A8) //contains the conversion results for samples collected with the sample sequencer
# define ALTCLKCFG      *((volatile uint32_t *)0x400FE138) 
# define ADCSSTSH3      *((volatile uint32_t *)0x400380BC) //controls the sample period size for the sample in sequencer 3.
# define ADCSAC         *((volatile uint32_t *)0x40038030) //This register controls the amount of hardware averaging applied to conversion results

//ADC interrupt setup
# define ADCIM_ADC0     *((volatile uint32_t *)0x40038008) //controls whether the sample sequencer and digital comparator raw interrupt signals are sent to the interrupt controller.
# define ADCRIS_ADC0    *((volatile uint32_t *)0x40038004) //shows the status of the raw interrupt signal of each sample sequencer. 
# define ADCISC_ADC0    *((volatile uint32_t *)0x4003800C) //clears sample sequencer interrupt conditions and shows the status of interrupts
# define ADCDCISC_ADC0  *((volatile uint32_t *)0x40038034) //provides status and acknowledgement of digital comparator interrupts



/*Interrupts Related Registers.................................*/

// NVIC interrupt registers
# define NVIC_EN0       *((volatile uint32_t *)0xE000E100) // Interrupt Enable in NVIC
# define NVIC_EN1       *((volatile uint32_t *)0xE000E104) // Interrupt Enable in NVIC
# define NVIC_PRI1      *((volatile uint32_t *)0xE000E404) // Interrupt priority for interrupt 4 (GPIO port E)
# define NVIC_PRI4      *((volatile uint32_t *)0xE000E410) // Interrupt priority for interrupt 19 (Timer 0A)
# define NVIC_PRI12     *((volatile uint32_t *)0xE000E430) // Interrupt priority for interrupt 51 (GPIO port J)

// GPIO interrupt registers
# define GPIOIS_PORTE   *((volatile uint32_t *)0x40059404) //Setting a bit to detect levels
# define GPIOIS_PORTJ   *((volatile uint32_t *)0x40060404) 
# define GPIOIBE_PORTE  *((volatile uint32_t *)0x40059408) //setting it allows both edges to cause interrupts (cannot be co-used with IEV
# define GPIOIBE_PORTJ  *((volatile uint32_t *)0x40060408) 
# define GPIOIEV_PORTE  *((volatile uint32_t *)0x4005940C) //Setting a bit to detect rising edges or high levels
# define GPIOIEV_PORTJ  *((volatile uint32_t *)0x4006040C) 
# define GPIOIM_PORTE   *((volatile uint32_t *)0x40059410) //interrupt mask register, allows interrupts to be sent to the interrupt controller
# define GPIOIM_PORTJ   *((volatile uint32_t *)0x40060410) 
# define GPIOICR_PORTE  *((volatile uint32_t *)0x4005941C) //clear interrupt and restart
# define GPIOICR_PORTJ  *((volatile uint32_t *)0x4006041C)

/*Timer Related Registers.................................*/

# define RCGCTIMER      *((volatile uint32_t *)0x400FE604) //enable and disable 16/32-bit timer modules in Run mode.
# define GPTMCFG_TIMER0 *((volatile uint32_t *)0x40030000) //determines whether the GPTM is in 32- or 16-bit mode
# define GPTMCFG_TIMER1 *((volatile uint32_t *)0x40031000) 
# define GPTMTAMR_TIMER0 *((volatile uint32_t *)0x40030004) //controls the modes for Timer A when it is used individually.
# define GPTMTAMR_TIMER1 *((volatile uint32_t *)0x40031004) 
# define GPTMCTL_TIMER0 *((volatile uint32_t *)0x4003000C) //enables other features such as timer stall and the output trigger.
# define GPTMCTL_TIMER1 *((volatile uint32_t *)0x4003100C) 
# define GPTMTAILR_TIMER0 *((volatile uint32_t *)0x40030028) //determines whether the timer is counting up or down
# define GPTMTAILR_TIMER1 *((volatile uint32_t *)0x40031028) 
# define GPTMRIS_TIMER0 *((volatile uint32_t *)0x4003001C) //shows the state of the GPTM's internal interrupt signal
# define GPTMRIS_TIMER1 *((volatile uint32_t *)0x4003101C) 
# define GPTMIMR_TIMER0 *((volatile uint32_t *)0x40030018) //enable/disable GPTM controller-level interrupts
# define GPTMIMR_TIMER1 *((volatile uint32_t *)0x40031018) 
# define GPTMICR_TIMER0 *((volatile uint32_t *)0x40030024) //used to clear the status bits in the GPTMRIS and GPTMMIS registers (set 1 to clear)
# define GPTMICR_TIMER1 *((volatile uint32_t *)0x40031024) 
# define GPTMADCEV_TIMER0 *((volatile uint32_t *)0x40030070) //allows software to enable/disable GPTM ADC trigger events.
# define GPTMADCEV_TIMER1 *((volatile uint32_t *)0x40031070) //allows software to enable/disable GPTM ADC trigger events.



/*GPIO peripherals related registers.......................................*/

//Register 89: General-Purpose Input/Output Run Mode Clock Gating Control
# define RCGCGPIO       *((volatile uint32_t *)0x400FE608)
# define RCGCGPIO_R0 0x1 //port A
# define RCGCGPIO_R1 0x2 //port B
# define RCGCGPIO_R4 0x10 //port E
# define RCGCGPIO_R5 0x20 //port F
# define RCGCGPIO_R8 0x100 //port J
# define RCGCGPIO_R12 0x1000 //port N

//Register 1: GPIO Data (GPIODATA), offset 0x000 (3FC to access all bits)
# define GPIODATA_PORTB *((volatile uint32_t *)0x400593FC)
# define GPIODATA_PORTE *((volatile uint32_t *)0x4005C3FC)
# define GPIODATA_PORTF *((volatile uint32_t *)0x4005D3FC)
# define GPIODATA_PORTJ *((volatile uint32_t *)0x400603FC)
# define GPIODATA_PORTN *((volatile uint32_t *)0x400643FC)

//Register 2: GPIO Direction (GPIODIR), offset 0x400
# define GPIODIR_PORTB *((volatile uint32_t *)0x40059400)
# define GPIODIR_PORTE *((volatile uint32_t *)0x4005C400)
# define GPIODIR_PORTF *((volatile uint32_t *)0x4005D400)
# define GPIODIR_PORTJ *((volatile uint32_t *)0x40060400)
# define GPIODIR_PORTN *((volatile uint32_t *)0x40064400)

//Setting a bit in this register configures the corresponding GPIO line to be controlled by an associated peripheral.
# define GPIOAFSEL_PORTA *((volatile uint32_t *)0x40058420)
# define GPIOAFSEL_PORTB *((volatile uint32_t *)0x40059420)
# define GPIOAFSEL_PORTE *((volatile uint32_t *)0x4005C420)

//pull-up select
//When a bit is set, a weak pull-up resistor on the corresponding GPIO signal is enabled.
# define GPIOPUR_PORTJ *((volatile uint32_t *)0x40060510)

//Register 18: GPIO Digital Enable (GPIODEN), offset 0x51C
# define GPIODEN_PORTA *((volatile uint32_t *)0x4005851C)
# define GPIODEN_PORTB *((volatile uint32_t *)0x4005951C)
# define GPIODEN_PORTE *((volatile uint32_t *)0x4005C51C)
# define GPIODEN_PORTF *((volatile uint32_t *)0x4005D51C)
# define GPIODEN_PORTJ *((volatile uint32_t *)0x4006051C)
# define GPIODEN_PORTN *((volatile uint32_t *)0x4006451C)

//The GPIOLOCK register enables write access to the GPIOCR register
# define GPIOLOCK_PORTJ *((volatile uint32_t *)0x40060520)

//If a bit in the GPIOCR register is set, the data written to registersis committed to the register and reflects the new value.
# define GPIOCR_PORTJ *((volatile uint32_t *)0x40060524)

//The GPIOAMSEL register controls isolation circuits to the analog side of a unified I/O pad
# define GPIOAMSEL_PORTB *((volatile uint32_t *)0x40059528)
# define GPIOAMSEL_PORTE *((volatile uint32_t *)0x4005C528)

/*MACROS.....................................................*/
# define LED1 0x2
# define LED2 0x1
# define LED3 0x10
# define LED4 0x1
# define SW1 0x1
# define SW2 0x2
# define PE0 0x1 //start/stop button
# define PE1 0x2 //pedestrian button
# define PE2 0x4 //red
# define PE3 0x8 //yellow
# define PE5 0x20//green


/*Function prototypes........................................*/
//initializations and setups
void int_led_init( );            //internal LEDs initialization
void int_switch_init( );         //external SWs iniatialization

void ext_LED_init( );            //external LEDs initialization
void ext_switch_init( );         //external SWs initialization

void timer_init( );              //timer0A initialization
void timer_interrupt_init( );    //timer0A interrupt initialization
void timer_interrupt_set( );     //timer0A interrupt setup
void resetTimer();
void Timer0A_Handler ( );        //timer0A ISR

void GPIO_J_interrupt_init( );   //GPIOJ interrupt initialization
void GPIO_J_interrupt_set( );    //GPIOJ interrupt setup
void GPIO_J_Handler ( void );    //GPIOJ ISR

void timers_init( );              //timer0A, 1A initialization
void timers_interrupt_init( );    //timer0A, 1A interrupt initialization
void timers_interrupt_set( );     //timer0A, 1A interrupt setup
void resetTimer0();              //timer0A reset
void Timer0A_Handler ( );        //timer0A ISR
void resetTimer1();              //timer1A reset
void Timer1A_Handler ( );        //timer1A ISR

void adc0_init(void);            //initialize ADC0
void adc0_interrupt_setup(void); //initialize ADC0 interrupt
void resetADC0(void);            //reset ADC0 interrupt
void ADC0_Handler(void);         //ADC0 ISR

void uart_init(void);            //initialize UART
void bluetooth_init(void);       //initialize bluetooth

//helper functions

//Lab2:
unsigned long switch_input(unsigned long switch_num);   //detects the switch input
void LED_on(unsigned char led);                         //turns on external led
void LED_off(unsigned char led);                        //turns off external led
char GPTM_polling();                                    //poll flag from timer0A countdown

//Lab3:
char GPTM_timer0_polling();                             //poll flag from timer0A countdown
char GPTM_timer1_polling();                             //poll flag from timer1A countdown
unsigned char ADC0_polling(void);                       //poll flag from ADC0
unsigned int ADC0_data(void);                           //return 12-bit data from ADC0
unsigned char UART0_polling(void);                      //poll busy flag from UART0
void write_UART0_data(char data);                       //write data to UART0
void printString(char string[]);                        //print a string to putty
void printTemp();                                       //print temperature using printString
unsigned char busyFlag();                               //poll busy flag from UART2
void write_UART2_data(char data);                       //write data to UART0
void printStringBluetooth(char string[]);               //print a string to putty
unsigned char receiveFlag(void);                        //check if data has been received

//Lab4:
void LCD_setup();                                       //setup the LCD with the background and buttons
void fsm_LCD();                                         //implement the traffic light's fsm with lcd
char validPress();                                      //determine valid press of buttons on LCD


//Main functions in Lab 2:
void flashing();                        //task1a
void fsm();                             //task1b
void flashing_by_timer_interrupt();     //task2a
void led_by_sw_interrupt();             //task2b
void fsm_by_timer_interrupt();          //task2c

//Main functions in Lab 3:
void blinking();                        //task1
void temp_reading();                    //task2A
void bluetoothComm();                   //task2B

//Main functions in Lab 4:
void tempReadingOnLCD();                //task1
void trafficLight_LCD();                //task2

# endif //MY_HEADER_H

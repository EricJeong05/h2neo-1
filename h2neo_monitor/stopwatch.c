/*
 * scrap.c
 *
 * This file contains all the unorganized methods. These should be eventually
 * moved to source files with descriptive names (just copy paste).
 *
 *  Created on: Jul 24, 2020
 *      Author: Jenny Cho
 */
#include <msp430.h>
#include "test.h"
#include "nokia5110.h"

extern unsigned long int tic;
extern unsigned short int dropStopwatch;
extern unsigned char butFLG;  // button flag

/*******************************************************************************
 * Initialize Timer0_A5
 ******************************************************************************/
void Timer0_A5_Init(void)
{
	TA0CCR0 	 =  0; 		//Initially, Stop the Timer
	TA0CTL		 =  TASSEL_2 + ID_0 + MC__UP; //Select SMCLK, SMCLK/1, Up Mode
	TA0CCTL0	|=  CCIE;		//Enable interrupt on TA0.0
//	TA0CCR0		 =  ;		//Period of 50ms or whatever interval you like.
}


/*******************************************************************************
 * Delay msecs milliseconds of time based on 1MHz clock
 ******************************************************************************/
void delayMS(int ms)
{
	tic = 0; //Reset Over-Flow counter
	// in general, Y MHz clock requires Y*1000 ticks for 1ms delay
	TA0CCR0 = 1000 - 1; //Start Timer, Compare value for Up Mode to get 1ms delay per loop
	//Total count = TACCR0 + 1. Hence we need to subtract 1.
	while(tic<=ms);

	TA0CCR0 = 0; //Stop Timer
}

/*******************************************************************************
 * Start Timer0_A5
 ******************************************************************************/
void startTimer0_A5(void)
{
	tic = 0; //Reset Over-Flow counter
	dropStopwatch = 0; // reset dropStopwatch (For double drop solution)
	// in general, Y MHz clock requires Y*1000 ticks for 1ms delay
	TA0CCR0 = 1000 - 1;  // start timer; compare value (up mode): 1 ms
//	P1OUT |= BIT0;
}


/*******************************************************************************
 * Stop Timer0_A5
 ******************************************************************************/
void stopTimer0_A5(void)
{
	TA0CCR0 = 0; // stop Timer
//	P1OUT &= ~BIT0; //Drive P1.0 LOW - LED1 OFF
}

/*******************************************************************************
 * calculate seconds from given tics value
 ******************************************************************************/
void getSec(int tics)
{

}






/*******************************************************************************
 * Timer 0 A0 Interrupt Service Routine
 ******************************************************************************/
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR( void )
{
	/* INCREMENT GLOBAL VARIABLES HERE:
	 *
	 * Will jump in here when TA0R reaches the value stored in TA0CCR0 during setup.
	 * Count the number of tics to equal a second, then increment seconds.
	 * Count the number of seconds to increment minutes. You get it.
	 *
	 * Don�t forget to update the LCD Display with the current time here if you
	 * are not doing that in the main loop.
	 */
	tic++;  // increment over-flow counter
	dropStopwatch++;
}


///*******************************************************************************
// * PORT1 Interrupt Service Routine
// ******************************************************************************/
//#pragma vector=PORT1_VECTOR
//__interrupt void Port_1_ISR( void )
//{
//	if (P1IFG & BIT1) {
//		butFLG = 1;
//		_delay_cycles(20000);	// debouncing
//		P1IFG &= ~BIT1;				// P1.1 interrupt flag cleared
//	}
//}

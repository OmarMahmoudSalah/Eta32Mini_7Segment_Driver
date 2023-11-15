/*
 * main.c
 * Created on: Sep 10, 2023
 * Author: Omar
 *
 *      Use ATmega32 Microcontroller with frequency 16Mhz.
 *      Total Required Ticks for 1 sec = 15625
 */

//////// Pre Processor Directives
#include "sevenseg.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
//////// Global Variable Deceleration
unsigned char second = 0;
unsigned char tick = 0;
unsigned char min = 0;
unsigned char hour = 0;

//unsigned char time[3]={0,0,0};

void Timer1_Initilaztion(void) {
	/*  Description :
	 * 	TCCR1A -  :
	 * 		Using Channel A in TIM1 ,  Bit 3 – FOC1A: =1
	 * 	TCCR1B :
	 * 		WGM12 =1 -  Mode 4 CTC OCR1A
	 * 		CS10,CS12 =1  - clkI/O/1024 (From prescaler)
	 * 	OCR1A -Output Compare Register 1 A : =1000
	 * 	TIMSK  Timer/Counter Interrupt Mask Register:
	 * 		OCIE1A =1
	 */

	TCCR1A = (1 << FOC1A);
	TCCR1B = (1 << WGM12) | (1 << CS10) | (1 << CS12);
	OCR1A = 15625;
	TIMSK |= (1 << OCIE1A);
}
ISR(TIMER1_COMPA_vect) {
	/*
	 * Description :
	 * Every Second (according to above calculation)AVR Sends an ISR
	 * 60 Second = 1 Min and 0 Second
	 * 60 Min = 1 HR and 0 Min and 0 Second
	 * Count Every ISR to Use Timer
	 *
	 */

	second++;
	tick++;


	if (second == 60) {
		second = 0;
		min++;
	}


	if (min == 60) {
		second = 0;
		min = 0;
		hour++;
	}
	if (hour == 24) {
		second = 0;
		min = 0;
		hour = 0;
	}
}



int main() {

	Timer1_Initilaztion();
	SEVENSEG_init(3);

	while (1) {
		SEVENSEG_displayNum_Ndec(second);
	}


}

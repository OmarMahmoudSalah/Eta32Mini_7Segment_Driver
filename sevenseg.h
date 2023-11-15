/*
 * sevenseg.h
 *
 *  Created on: Oct 5, 2023
 *      Author: Omar
 */

#include "gpio.h"
#include "std_types.h"
#ifndef SEVENSEG_H_
#define SEVENSEG_H_

					/*ENABLE DIGIT*/
#define EN_DIG_PORT			PORTC_ID
#define EN_DIG_1			PIN6_ID
#define EN_DIG_2			PIN7_ID

					/*LEDS*/
#define LEDS_PORT			PORTA_ID

#define LED_A				PIN1_ID
#define LED_B				PIN2_ID
#define LED_C				PIN3_ID
#define LED_D				PIN4_ID
#define LED_E				PIN5_ID
#define LED_F				PIN6_ID
#define LED_G				PIN7_ID
					/*DOT*/
#define DOT_PORT			PORTB_ID
#define DOT_PIN				PIN0_ID


void SEVENSEG_init(uint8);
void SEVENSEG_displayNum_Ndec(uint8);
//void SEVENSEG_displayNum2(uint8);


#endif /* SEVENSEG_H_ */

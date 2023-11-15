/*
 * sevenseg.c
 *
 *  Created on: Oct 5, 2023
 *      Author: Omar
 */

#include "sevenseg.h"
#include <util/delay.h>
uint8 NumbertoAdj = 0; // Flag to indicate whether number adjustment is needed

/////////////////////////////////////////////////////////
static void display(uint8 number); // Function to display a single digit
/////////////////////////////////////////////////////////

/*
 * The function initializes the seven-segment display by setting the pins for the LEDs and digit enable pins as outputs.
 The switch statement is used to set the NumbertoAdj variable based on the numofdigts parameter. This variable is used to adjust the number that is displayed on the seven-segment display.
 The GPIO_writePin() function is used to set the state of the digit enable pins. This determines which digit is currently being displayed.
 *
 * This Helps with Dynamic Number Viewing in runtime .
 *  1 - Enables First Dig. Only
 *  2 - Enables Second Dig. Only
 *  3- Both Running
 *
 * */

void SEVENSEG_init(uint8 numofdigts) {
	GPIO_setupPinDirection(LEDS_PORT, LED_A, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT, LED_B, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT, LED_C, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT, LED_D, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT, LED_E, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT, LED_F, PIN_OUTPUT);
	GPIO_setupPinDirection(LEDS_PORT, LED_G, PIN_OUTPUT);
	// Set digit enable pins as outputs
	GPIO_setupPinDirection(EN_DIG_PORT, EN_DIG_1, PIN_OUTPUT);
	GPIO_setupPinDirection(EN_DIG_PORT, EN_DIG_2, PIN_OUTPUT);
	switch (numofdigts) {
	default:
	case 1: // Enable only the first digit
		NumbertoAdj = 0; // No adjustment needed
		GPIO_writePin(EN_DIG_PORT, EN_DIG_1, LOGIC_HIGH); // Enable digit 1
		GPIO_writePin(EN_DIG_PORT, EN_DIG_2, LOGIC_LOW); // Disable digit 2
		break;
	case 2:
		NumbertoAdj = 0;
		GPIO_writePin(EN_DIG_PORT, EN_DIG_1, LOGIC_LOW);
		GPIO_writePin(EN_DIG_PORT, EN_DIG_2, LOGIC_HIGH);
		break;
	case 3: // Enable both digits (number adjustment needed)
		NumbertoAdj = 1; // Adjustment required
		break;
	}

}

/*
 * Displays the decimal representation of the 'number' parameter on the seven-segment display.
 *
 * If NumbertoAdj flag is set, it indicates that the number needs to be split into tens and units digits and displayed accordingly.
 * The first digit displays the units digit and the second digit displays the tens digit.
 *
 * If NumbertoAdj flag is not set, it indicates that the number should be displayed directly without any adjustment.
 *
 */
void SEVENSEG_displayNum_Ndec(uint8 number) {
	if (NumbertoAdj == 1) {
		GPIO_writePin(EN_DIG_PORT, EN_DIG_1, LOGIC_HIGH);
		GPIO_writePin(EN_DIG_PORT, EN_DIG_2, LOGIC_LOW);
		display(number % 10);
		_delay_ms(5);// Add a small delay to avoid flickering - adjust it for better visibility
		GPIO_writePin(EN_DIG_PORT, EN_DIG_2, LOGIC_HIGH);
		GPIO_writePin(EN_DIG_PORT, EN_DIG_1, LOGIC_LOW);
		display(number / 10);
		_delay_ms(5);
	} else {
		display(number);
	}

}

/**
 * Displays a single digit on the seven-segment display
 */

static void display(uint8 number) {
	switch (number) {
	case 0:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_LOW);
		break;
	case 1:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_LOW);
		break;
	case 2:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_HIGH);
		break;
	case 3:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_HIGH);
		break;
	case 4:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_HIGH);
		break;
	case 5:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_HIGH);
		break;
	case 6:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_HIGH);
		break;
	case 7:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_LOW);
		break;
	case 8:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_HIGH);
		break;
	case 9:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_HIGH);
		break;
	case 10:
		GPIO_writePin(LEDS_PORT, LED_A, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_B, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_C, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_D, LOGIC_LOW);
		GPIO_writePin(LEDS_PORT, LED_E, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_F, LOGIC_HIGH);
		GPIO_writePin(LEDS_PORT, LED_G, LOGIC_HIGH);
		break;
	}
}
/*
 *
 * Another Valid Method but more calling left as a comment
 *
 void SEVENSEG_displayNum2(uint8 number1) {
 SEVENSEG_init(1); //Enable
 SEVENSEG_displayNum_Ndec(number1 % 10);
 _delay_ms(20);
 SEVENSEG_init(2); //Enable
 SEVENSEG_displayNum_Ndec(number1 / 10);
 _delay_ms(20);
 }
 *
 *
 *
 */

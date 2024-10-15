/*keypad.c
 * This file contains the keypad functions definitions
 * 20,April 2024
 * REFERENCE:https://www.youtube.com/watch?v=R5sv1hbONrk
 *  Created on: Apr 24, 2024
 *      Author: Aysvarya
 */


#include "keypad.h"


char key_pressed[5] = { 0 };
volatile uint8_t buttonState[3][3] = { 0 }; // button state is volatile
uint32_t volatile *RCC_Base_Addr = (uint32_t*) 0x40023830;  // rcc address + ahb1 offset address of port b
uint32_t volatile *GPIOIntput = (uint32_t*) 0x40020410;  // offset address of input data register is 0x10
uint32_t volatile *GPIOModer = (uint32_t*) 0x40020400;    //base address(0x4002 0400) of port b + moder offset address
uint32_t volatile *GPIOOutput = (uint32_t*) 0x40020414;  // offset address of output data register is 0x14
uint32_t volatile *GPIOOspeed = (uint32_t*) 0x40020408; // offset address of output speed register is 0x08
uint32_t volatile *GPIOPullup = (uint32_t*) 0x4002040C;  // offset address of pull up/ pull down register is 0x0c

void init_keypad(void) {

	//Base address RCC 0x4002 3800 + Address offset of RCC AHB1 = 0x30
	//Base address GPIOE 0x4002 1000 + Address offset of GPIO Moder = 0x00
	//GPIO Port o/p data register = 0x14

	*RCC_Base_Addr |= 1 << 1; // enable the gpiob with clock
	*GPIOModer &= ~(0xFF << 14); //Cols as Input , so 00 to PB7,PB8,PB9 as input
	*GPIOModer |= (0x55 << 6); //Rows as  output , so 01 for PB3, PB4, PB5, PB6 as output
	*GPIOOspeed &= ~(0xFF << 6);
	*GPIOPullup &= ~(0xFF << 14);// setting pull up resistors for columns
	*GPIOPullup |= (0x15 << 14);

}


char* key_input(void) {
//*****************************************ROW 1*********************************************************//
	char ch = '\0';
	bool button_pressed = false;
	int i = 0;

	while (1) {
		*GPIOOutput |= (0xFF << 3);	// set the rows high

		*GPIOOutput &= ~(1 << 3);	// row 1 (PB3) is low

		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 7)) && !buttonState[0][0]) {	// Check GPIO state
			button_pressed = true;
			ch = '1';
			buttonState[0][0] = 1;
			delay(100); // Debounce delay

		} else if (*GPIOIntput & (1 << 7)) {
			buttonState[0][0] = 0;
		}
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 8)) && !buttonState[0][1]) {	// Check GPIO state
			button_pressed = true;
			ch = '2';
			buttonState[0][1] = 1;
			delay(100); // Debounce delay
		} else if (*GPIOIntput & (1 << 8)) {
			buttonState[0][1] = 0;
		}
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 9)) && !buttonState[0][2]) {	// Check GPIO state
			button_pressed = true;
			ch = '3';
			buttonState[0][2] = 1;
			delay(100); // Debounce delay
		} else if (*GPIOIntput & (1 << 9)) {
			buttonState[0][2] = 0;
		}

//*****************************************ROW 2*********************************************************//

		*GPIOOutput |= (0xFF << 3);	// set the rows high

		*GPIOOutput &= ~(1 << 4);	// row 2 (PB4) is low
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 7)) && !buttonState[1][0]) {	// Check GPIO state
			button_pressed = true;
			ch = '4';
			buttonState[1][0] = 1;
			delay(100); // Debounce delay

		} else if (*GPIOIntput & (1 << 7)) {
			buttonState[1][0] = 0;
		}
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 8)) && !buttonState[1][1]) {	// Check GPIO state
			button_pressed = true;
			ch = '5';
			buttonState[1][1] = 1;
			delay(100); // Debounce delay
		} else if (*GPIOIntput & (1 << 8)) {
			buttonState[1][1] = 0;
		}
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 <<9)) && !buttonState[1][2]) {	// Check GPIO state
			button_pressed = true;
			ch = '6';
			buttonState[1][2] = 1;
			delay(100); // Debounce delay
		} else if (*GPIOIntput & (1 << 9)) {
			buttonState[1][2] = 0;
		}

//*****************************************ROW 3*********************************************************//
		*GPIOOutput |= (0xFF << 3);	// set the rows high
		// check if column is low, then that (row,col) is pressed
		*GPIOOutput &= ~(1 << 5);	// row 3 (PB5) is low
		if (!(*GPIOIntput & (1 <<7)) && !buttonState[2][0]) {	// Check GPIO state
			button_pressed = true;
			ch = '7';
			buttonState[2][0] = 1;
			delay(100); // Debounce delay

		} else if (*GPIOIntput & (1 << 7)) {
			buttonState[2][0] = 0;
		}
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 8)) && !buttonState[2][1]) {	// Check GPIO state
			button_pressed = true;
			ch = '8';
			buttonState[2][1] = 1;
			delay(100); // Debounce delay
		} else if (*GPIOIntput & (1 << 8)) {
			buttonState[2][1] = 0;
		}
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 9)) && !buttonState[2][2]) {	// Check GPIO state
			button_pressed = true;
			ch = '9';
			buttonState[2][2] = 1;
			delay(100); // Debounce delay
		} else if (*GPIOIntput & (1 << 9)) {
			buttonState[2][2] = 0;
		}

//*****************************************ROW 4*********************************************************//

		*GPIOOutput |= (0xFF << 3);	// set the rows high

		*GPIOOutput &= ~(1 << 6);	//  (pb6) is low 4th row
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 7)) && !buttonState[3][0]) {	// Check GPIO state
			button_pressed = true;
			ch = '*';
			buttonState[3][0] = 1;
			delay(100); // Debounce delay

		} else if (*GPIOIntput & (1 << 7)) {
			buttonState[3][0] = 0;
		}
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 8)) && !buttonState[3][1]) {	// Check GPIO state

			button_pressed = true;
			ch = '0';
			buttonState[3][1] = 1;
			delay(100); // Debounce delay
		} else if (*GPIOIntput & (1 << 8)) {
			buttonState[3][1] = 0;
		}
		// check if column is low, then that (row,col) is pressed
		if (!(*GPIOIntput & (1 << 9)) && !buttonState[3][2]) {	// Check GPIO state
			button_pressed = true;
			ch = '#';
			buttonState[3][2] = 1;
			delay(100); // Debounce delay
		} else if (*GPIOIntput & (1 << 9)) {
			buttonState[3][2] = 0;
		}
		if (ch == '#') // if delimiter is pressed
			break;
		if ((button_pressed == true) && (!((!(ch == '*')) || (ch == '#')))) {

		} else if ((button_pressed == true) && ((ch >= '0') && (ch <= '9'))) {
			key_pressed[i]= ch;
			i++;
			ch = '\0';
		}
	}
	return key_pressed;

}


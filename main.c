/*THIS FILE CONTAINS THE MAIN FUNCTION
 * 20,April 2024
 *AUTHOR -Aysvarya Gopinath
 */

#include "delay.h"
#include "stdio.h"
#include "rfid.h"
#include "delay.h"
#include "keypad.h"
#include "oled.h"
#include "cart.h"
#include "stdio.h"
#include "fonts.h"
#include"bluetooth.h"

int main(void) {
	systick_init_ms(16000000);        // initialise 16MHz clock
	rc522_init();					// Initialize RFID reader module
	oled_init();					// Initialize OLED display

	init_keypad();		// Initialize keypad
	UART_init();		// for bluetooth
	tags_init();          // for ag attributes
	write_uart_string("\n\rWelcom to our store. \n\r");
	write_uart_string("\n\r We help you managing your shopping. \n\r");
	oled_gotoXY(0, 0);			// Set the cursor to (0,0) location on the OLED
	oled_puts("    Welcome ", &Font_7x10, 1);// Set the default message to be displayed on OLED
	oled_gotoXY(0, 10);			// Set the cursor to (0,10) location
	oled_clear_line();			// Clear the line
	oled_gotoXY(0, 20);			// Set the cursor to (0,20) location
	oled_clear_line();			// Clear the line
	oled_update_screen(); 		// Display the content set above on OLED
	while (1) {
		add_item(); // function to add items
		return 0;
	}
}

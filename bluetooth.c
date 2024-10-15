/*
 * bluetooth.c
 * This file contains the uart functions for bluetooth communication
 * 20,April 2024
 * AUTHOR -Aysvarya Gopinath & Gazelle
*/


// Header file for STM32F411VET Discovery Board
#include "stm32f4xx.h"
#include "stdio.h"
#include"cart.h"
#include "bluetooth.h"

#define UART_TX (7 << 8)
#define UART_RX (7 << 12)

int added[20]; // track of the products added
 int removed[20]; // track of products removed


//UART Initializing
void UART_init()
{
	// Enabling UART clock
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN; //(0x1UL << (17U))
	//Enabling CLK for PORT A
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN ;

	// select USART2 functionality on
	// Pin 2 and Pin 3 of Port A
	// Alternate Function
	GPIOA->MODER |= GPIO_MODER_MODER2_1 ;//PIN2
	GPIOA->MODER |=GPIO_MODER_MODER3_1 ;//PIN3
	GPIOA->AFR[0]  |= UART_TX; //Enabling Tx
	GPIOA->AFR[0]  |= UART_RX; //Enabling Rx


	//	Select the desired baud rate using the USART_BRR register. //9600
	USART2->BRR |= 0x0683;

	// Set Transmit Enable bit USART2->CR1
	USART2->CR1 |= USART_CR1_TE;

	// Set Receive Enable bit
	USART2->CR1 |= USART_CR1_RE;

	// Enable the USART by writing the UE bit in USART_CR1 register to 1
	USART2->CR1 |= USART_CR1_UE;
}

// Transmit a single character over UART
void write_uart_char(char ch)
{
	// Wait till transmission is complete
	while ((USART2->SR & USART_SR_TC)==0);
	USART2->SR &= ~USART_SR_TC;// Clear transmission complete bit
	USART2-> DR = ch & 0xFF;// Write data into data register to start transmission

}

// Transmit a string character
void write_uart_string(char * str)
{
	// Transmit each character of the string one at a time
	// until the end of the string ('\0') is reached
	while(*str!='\0')
	{
			write_uart_char(*str++);
	}
}


void sum_amt(void)
{
	char buffer[20]; // Buffer to hold the string format of the total sum
	    // Convert tot_sum to a string
	    sprintf(buffer, "%d", tot_sum);
	    // Print the message along with the total sum
	    write_uart_string("Cost of items currently in cart  is");
	    write_uart_string(buffer); // Print the total sum
	    write_uart_char('$');
	    write_uart_string("\n\r"); // New line

}

void num_tot(void){

	char buffer[20]; // Buffer to hold the string format of the total number
	    // Convert tot_num to a string
	    sprintf(buffer, "%d", tot_num);
	    // Print the total number
	    write_uart_string("Number of items currently in cart is");
	    write_uart_string(buffer); // Print the total number
	    write_uart_string("\n\r"); // New line

}
//menu
void menu (void){
	write_uart_string("\n\r|---------------------------------------------------------|\n\r");
	write_uart_string("\n\r|                             MENU                        |\n\r");
	write_uart_string("\n\r|---------------------------------------------------------|\n\r");
	write_uart_string("\n\r|Press 9 to display the total bill summary of all items   |\n\r");
	write_uart_string("\n\r|Press 8 to display the cost of items currently in cart   |\n\r");
	write_uart_string("\n\r|Press 0 to display the number of items currently in cart |\n\r");
	write_uart_string("\n\r|---------------------------------------------------------|\n\r");
}


// bill summary
void display_bill(void)
{
	 char buffer[20]; // Buffer to hold the string representation of the total sum

	write_uart_string("\n\rThe total bill for 3 products is 200$\n\r");

	for (int i = 0; i < added_count; i++) { /// display added items
		if(added[i]==1)
		{
			write_uart_string("\n\rPRODUCT 1 added +50$");
		}
		if (added[i]==2){
			write_uart_string("\n\rPRODUCT 2 added +70$");
		}
		if (added[i]==3){
			write_uart_string("\n\rPRODUCT 3 added +80$");
		}
		if(added[i]==4){
			write_uart_string("\n\rPRODUCT 4 added +100$");
		}
	  }

	    // Display removed products
	    for (int i = 0; i < removed_count; i++) {
	    	if(removed[i]==1)
	    			{
	    				write_uart_string("\n\rPRODUCT 1 removed -50$");
	    			}
	    			if (removed[i]==2){
	    				write_uart_string("\n\rPRODUCT 2 removed -70$");
	    			}
	    			if (removed[i]==3){
	    				write_uart_string("\n\rPRODUCT 3 removed -80$");
	    			}
	    			if(removed[i]==4){
	    				write_uart_string("\n\rPRODUCT 4 removed -100$");
	    			}
	    }

	            sprintf(buffer, "%d", tot_sum);// Convert tot_sum to a string
	    	    // Print the message along with the total sum
	    	    write_uart_string("The total bill for 3 products is");
	    	    write_uart_string(buffer); // Print the total sum
	    	    write_uart_char('$');
	    	    write_uart_string("\n\r"); // New line


}







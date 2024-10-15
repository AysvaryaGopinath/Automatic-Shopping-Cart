/* i2c.c
 *This file contains the functions definitions for i2c api
 *20,April 2024
 *REFERENCE -https://blog.embeddedexpert.io/?p=613
 *      Author:Aysvarya
 */

#include "i2c.h"

void i2c_init(void) {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 				//enable gpioa clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN; 	            // gpioc enable clock
	RCC->APB1ENR |= RCC_APB1ENR_I2C3EN; 				//enable i2c3 clock
	GPIOA->MODER |= 2<<16; 							//set pa8 and pc9 to alternative function
	GPIOC->MODER |= 2<<18;
	GPIOA->AFR[1] |= 4<<0;           // set PA8 to SCL
	GPIOC->AFR[1] |= 4 << 4;             //set PC9 to SDA
	GPIOA->OTYPER |= GPIO_OTYPER_OT8; //set pa8  as open drain
	GPIOC->OTYPER |= GPIO_OTYPER_OT9; //set pc9 as open drain
	I2C3->CR1 = I2C_CR1_SWRST;
	I2C3->CR1 &= ~I2C_CR1_SWRST;  // software reset for i2c
	I2C3->CR2 |= 0x32; // maximum peripheral clock frequency 50Mhz
	I2C3->CCR |= 0x04 | (1 << 15) | (1 << 14); // fast mode is set before i2c is enabled
	I2C3->TRISE = 0x10; //output max rise in fast mode
	I2C3->CR1 |= I2C_CR1_PE;   // peripheral enable
}

void i2c_write_byte(char saddr, char maddr, char data) {
	while (I2C3->SR2 & I2C_SR2_BUSY)
	{;} 													//wait until bus not busy
	I2C3->CR1 |= I2C_CR1_START; 						//generate start
	while (!(I2C3->SR1 & I2C_SR1_SB))
	{;} 													//wait until start bit is set
	I2C3->DR = saddr << 1; 								// Send slave address
	while (!(I2C3->SR1 & I2C_SR1_ADDR))
	{;} 													//wait until address flag is set
	if(I2C3->SR2)
	{}										//clear SR2 by reading it
	while (!(I2C3->SR1 & I2C_SR1_TXE))
	{;} 													//Wait until Data register empty
	I2C3->DR = maddr; 									// send memory address
	while (!(I2C3->SR1 & I2C_SR1_TXE))
	{;} 													//wait until data register empty
	I2C3->DR = data;
	while (!(I2C3->SR1 & I2C_SR1_BTF))
		; 												//wait until transfer finished
	I2C3->CR1 |= I2C_CR1_STOP; 							//Generate Stop

}

void i2c_write_multi(char saddr, char maddr, char *buffer, uint8_t length) {

	while (I2C3->SR2 & I2C_SR2_BUSY)
		;           									//wait until bus not busy
	I2C3->CR1 |= I2C_CR1_START;                   		//generate start
	while (!(I2C3->SR1 & I2C_SR1_SB))
	{;}													//wait until start is generated
	I2C3->DR = saddr << 1;                 	 			// Send slave address
	while (!(I2C3->SR1 & I2C_SR1_ADDR))
	{;}        											//wait until address flag is set
	if(I2C3->SR2)
	{}									                //Clear SR2
	while (!(I2C3->SR1 & I2C_SR1_TXE))
		;           									//Wait until Data register empty
	I2C3->DR = maddr;                      				// send memory address
	while (!(I2C3->SR1 & I2C_SR1_TXE))
		;           									//wait until data register empty
	//sending the data
	for (uint8_t i = 0; i < length; i++) {
		I2C3->DR = buffer[i]; 							//filling buffer with command or data
		while (!(I2C3->SR1 & I2C_SR1_BTF))
			;
	}
	I2C3->CR1 |= I2C_CR1_STOP;							//wait until transfer finished

}

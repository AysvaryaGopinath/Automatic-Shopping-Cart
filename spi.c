/*spi.c
 *This file contains the definitions of spi api
 *This 20,April 2024
 *   AUTHOR -Aysvarya Gopinath
 */
#include "spi.h"
#include<stdio.h>
#include "delay.h"
#include "stm32f4xx.h"

#define GPIOE_EN (1 << 4)
#define SPI4_EN (1<<13)
#define GPIO_MODER2_ALT ( 2<<4)
#define GPIO_MODER5_ALT (2<< 10)
#define GPIO_MODER6_ALT (2<< 12)
#define GPIO_ALT5_PE2 (5<<8)
#define GPIO_ALT5_PE5 (5<<20)
#define GPIO_ALT5_PE6 (5<<24)
#define MSB_FIRST (0<<7)
#define CPOL (0<<0)
#define CPAH (0<<1)

void SPI_Init(void) {
	RCC->AHB1ENR |= GPIOE_EN; //enable clock for gpio E
	RCC->APB2ENR |= SPI4_EN; //enable clock for spi4
	GPIOE->MODER &= ~(GPIO_MODER_MODE2_0 | GPIO_MODER_MODE5_0
			| GPIO_MODER_MODE6_0);
	GPIOE->MODER |= GPIO_MODER2_ALT | GPIO_MODER5_ALT | GPIO_MODER6_ALT; // set the gpio to alternate function mode
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR2 | GPIO_OSPEEDER_OSPEEDR5
			| GPIO_OSPEEDER_OSPEEDR6; // high speed mode
	GPIOE->AFR[0] |= GPIO_ALT5_PE2 | GPIO_ALT5_PE5 | GPIO_ALT5_PE6; // specify the alternate function
	SPI4->CR2 = 0; // clear the flags in the register
	SPI4->CR1 = SPI_CR1_SSM | SPI_CR1_MSTR | SPI_CR1_BR_2 | SPI_CR1_SSI
			| MSB_FIRST | CPOL | CPAH;
	SPI4->CR1 |= SPI_CR1_SPE; //Enable SPI4

}

// spi tranmsit
int8_t SPI_Transmit(uint8_t *data, uint32_t size) {
	uint8_t i = 0;
	uint32_t start = millis();

	// clear data register before transmission
	if (SPI4->DR) {
	}
	// check the status register  is ready for SPI transmission
	if (SPI4->SR) {
	}

	while (i < size) { // until data size
		while (!((SPI4->SR) & SPI_SR_TXE)) {
			if (millis() - start > 1000) { // Wait for transmit buffer to be empty
				printf("Transmission timed out\r\n");
				return -1;
			}

			SPI4->DR = data[i];  // Transmit data byte by byte
			while (!(SPI4->SR & SPI_SR_BSY)) {
				if (millis() - start > 1000) {
					printf("Busy flag timed out\r\n");
					return -1;
				}
			}
			i++;
		}
		// Wait for Transmit buffer to be empty
		while (!((SPI4->SR) & SPI_SR_TXE)) {
			if (millis() - start > 1000) {
				printf("Transmission timed out\r\n");
				return -1;
			}
		}

		// Wait for transmit
		while ((SPI4->SR) & SPI_SR_BSY) {
			if (millis() - start > 1000) {
				printf("Busy flag timed out\r\n");
				return -1;
			}
		}

		//clear data register after transmission
		if (SPI4->DR) {
		}
		// check the status register it is done with SPI receiving
		if (SPI4->SR) {
		}
		return 0;
	}
}

// spi receive
int8_t SPI_Receive(uint8_t *data, uint32_t size) {

	while (size) {
		uint32_t start = millis();
		SPI4->DR = 0; // empty the data register to receive
		while (!(SPI4->SR & SPI_SR_RXNE)) {
			if (millis() - start > 200) {
				return -1;
			}
		}
		*data++ = (SPI4->DR); // retrieve the value in the data register
		size--;
	}
	return 0;
}


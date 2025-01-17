/*
 * delay.c
 *This function contains the delay function and related api definitions
 *      Author: Aysvarya
 *      20,April 2024
 */


#include "stm32f4xx.h"                  // Device header
#include "delay.h"

volatile uint32_t ms, rms;

void systick_init_ms(uint32_t freq) {
	__disable_irq();
	SysTick->LOAD = (freq / 1000) - 1;
	SysTick->VAL = 0;
	SysTick->CTRL = 7; //0b00000111;
	__enable_irq();
}

uint32_t millis(void) {
	__disable_irq();
	rms = ms; //store current ms in rms
	__enable_irq();
	return rms;
}

void SysTick_Handler(void) {
	ms++;	// Increment the milliseconds counter
}

void delay(uint32_t ms) {
	uint32_t start = millis();

	do {
		;
	} while (millis() - start < ms);

}

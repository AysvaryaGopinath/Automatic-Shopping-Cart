/*
 * oled.c
 *This file contains oled function definitions
 *This 20,April 2024
REFERENCE -https://blog.embeddedexpert.io/?p=613
 *      Author: Aysvarya
 */


#include "oled.h"

#define oled_WRITECOMMAND(command)      i2c_write_byte(oled_I2C_ADDR, 0x00, (command))
#define oled_DEACTIVATE_SCROLL           0x2E // Stop scroll

static char oled_Buffer[oled_WIDTH * oled_HEIGHT / 8]; //data buffer

typedef struct {
	uint16_t CurrentX;
	uint16_t CurrentY;
	uint8_t Initialized;
} oled_t;
static oled_t oled;
uint8_t oled_init(void) {
	i2c_init();
	oled_i2c_init();
	uint32_t p = 2500;//delay
	while (p > 0)
		p--;

	/* Init LCD */
	oled_WRITECOMMAND(0xAE); //display off
	oled_WRITECOMMAND(0x20); //Set Memory Addressing Mode
	oled_WRITECOMMAND(0x10); //00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	oled_WRITECOMMAND(0xB0); //Set Page Start Address for Page Addressing Mode,0-7
	oled_WRITECOMMAND(0xC8); //Set COM Output Scan Direction
	oled_WRITECOMMAND(0x00); //set low column address
	oled_WRITECOMMAND(0x10); //set high column address
	oled_WRITECOMMAND(0x40); //set start line address
	oled_WRITECOMMAND(0x81); //set contrast control register
	oled_WRITECOMMAND(0xFF);
	oled_WRITECOMMAND(0xA1); //set segment re-map 0 to 127
	oled_WRITECOMMAND(0xA6); //set normal display
	oled_WRITECOMMAND(0xA8); //set multiplex ratio(1 to 64)
	oled_WRITECOMMAND(0x3F); //
	oled_WRITECOMMAND(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	oled_WRITECOMMAND(0xD3); //set display offset
	oled_WRITECOMMAND(0x00); //not offset
	oled_WRITECOMMAND(0xD5); //set display clock divide ratio/oscillator frequency
	oled_WRITECOMMAND(0xF0); //set divide ratio
	oled_WRITECOMMAND(0xD9); //set pre-charge period
	oled_WRITECOMMAND(0x22); //
	oled_WRITECOMMAND(0xDA); //set com pins hardware configuration
	oled_WRITECOMMAND(0x12);
	oled_WRITECOMMAND(0xDB); //set vcomh
	oled_WRITECOMMAND(0x20); //0x20,0.77xVcc
	oled_WRITECOMMAND(0x8D); //set DC-DC enable
	oled_WRITECOMMAND(0x14); //
	oled_WRITECOMMAND(0xAF); //turn on oled panel

	oled_WRITECOMMAND(oled_DEACTIVATE_SCROLL);
	oled_fill(oled_COLOR_BLACK);	// Clear screen
	oled_update_screen();	// Update screen

	/* Set default values */
	oled.CurrentX = 0;
	oled.CurrentY = 0;

	oled.Initialized = 1;

	return oled.Initialized;
}

void oled_update_screen(void) {
	uint8_t m;

	for (m = 0; m < 8; m++) {
		oled_WRITECOMMAND(0xB0 + m);
		oled_WRITECOMMAND(0x00);
		oled_WRITECOMMAND(0x10);

		/* Write multi data */
		oled_i2c_write_multi(oled_I2C_ADDR, 0x40,
				&oled_Buffer[oled_WIDTH * m], oled_WIDTH);
	}
}

void oled_fill(oled_COLOR_t color) {
	/* Set memory */
	memset(oled_Buffer, (color == oled_COLOR_BLACK) ? 0x00 : 0xFF,
			sizeof(oled_Buffer));
}

void oled_draw_pixel(uint16_t x, uint16_t y, oled_COLOR_t color) {
	if (x >= oled_WIDTH || y >= oled_HEIGHT) {
		return;
	}

	/* Set color */
	if (color == oled_COLOR_WHITE) {
		oled_Buffer[x + (y / 8) * oled_WIDTH] |= 1 << (y % 8);
	} else {
		oled_Buffer[x + (y / 8) * oled_WIDTH] &= ~(1 << (y % 8));
	}
}

void oled_gotoXY(uint16_t x, uint16_t y) {
	/* Set write pointers */
	oled.CurrentX = x;
	oled.CurrentY = y;
}

char oled_putc(char ch, FontDef_t *Font, oled_COLOR_t color) {
	uint32_t i, b, j;

	/* Check available space in LCD */
	if (
	oled_WIDTH <= (oled.CurrentX + Font->FontWidth) ||
	oled_HEIGHT <= (oled.CurrentY + Font->FontHeight)) {
		return 0;
	}

	/* Go through font */
	for (i = 0; i < Font->FontHeight; i++) {
		b = Font->data[(ch - 32) * Font->FontHeight + i];
		for (j = 0; j < Font->FontWidth; j++) {
			if ((b << j) & 0x8000) {
				oled_draw_pixel(oled.CurrentX + j, (oled.CurrentY + i),
						(oled_COLOR_t) color);
			} else {
				oled_draw_pixel(oled.CurrentX + j, (oled.CurrentY + i),
						(oled_COLOR_t) !color);
			}
		}
	}

	/* Increase pointer */
	oled.CurrentX += Font->FontWidth;

	/* Return character written */
	return ch;
}

char oled_puts(char *str, FontDef_t *Font, oled_COLOR_t color) {
	/* Write characters */
	while (*str) {
		/* Write character by character */
		if (oled_putc(*str, Font, color) != *str) {
			/* Return error */
			return *str;
		}

		str++;
	}

	return *str;
}

void oled_clear_screen(void) {
	oled_fill(0);				// Fill the buffer with zeros
	oled_update_screen();		// Update the screen with the filled buffer
}

void oled_clear_line(void) {
	oled_puts("                  ", &Font_7x10, 1);	// Clear the whole line from the current cursor position
}

void oled_i2c_init(void) {

	uint32_t p = 250000;			// Wait for I2C initialization
	while (p > 0)
		p--;
}

void oled_i2c_write_multi(uint8_t address, uint8_t reg, char *data,
		uint16_t count) {
	i2c_write_multi(address, reg, data, count);		// I2C write multi-registers
}

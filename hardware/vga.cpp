/**
 * The VGA code
 *
 * @package CppOS
 * @since CppOS 1.0
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#include <stddef.h>
#include <stdint.h>

#ifndef VGA_H
#define VGA_H

class VGA {
private:
	size_t max_row;
	size_t max_column;

	size_t row;
	size_t column;
	uint8_t color;
	uint16_t* buffer;	

	void outb(unsigned short int, char);
public:
	VGA(size_t, size_t, size_t, size_t, uint8_t, uint16_t*);

	uint16_t make_entry(char, uint8_t);
	uint8_t make_color(unsigned short int, unsigned short int);

	void set_cursor(unsigned short int, unsigned short int);
	void set_color(uint8_t);
	void put_entry(char, uint8_t, size_t, size_t);
};

#endif

VGA::VGA(size_t a1, size_t a2, size_t a3, size_t a4, uint8_t a5, uint16_t* a6) {
	max_row = a1;
	max_column = a2;
	row = a3;
	column = a4;
	color = a5;
	buffer = a6;
}

void VGA::outb(unsigned short int port, char data) {
	asm("outb %%al, %%dx;" : : "d"(port), "a"(data));
}

void VGA::set_cursor(unsigned short int r, unsigned short int c) {
	unsigned short int port = 0x3D4;
	unsigned char data = 0x0E;
	unsigned int position = r * (max_column + 1) + c;
	outb(port, data);
	port = 0x3D5;
	data = (position >> 8) & 0xFF;
	outb(port, data);
	port = 0x3D4;	
	data = 0x0F;
	outb(port, data);
	port = 0x3D5;
	data = position & 0xFF;
	outb(port, data);
}

uint8_t VGA::make_color(unsigned short int fg, unsigned short int bg) {
	return fg | bg << 4;
}

uint16_t VGA::make_entry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

/**
 * Black: 0, Blue: 1, Green: 2, Cyan: 3, Red: 4, Magenta: 5, Brown: 6, White: 15
 * Light Grey: 7, Dark Grey: 8, Light Blue: 9, Light Green: 10, Light Cyan: 11, Light Red: 12, Light Magenta: 13, Light Brown: 14
 */

void VGA::set_color(uint8_t colorx) {
	color = colorx;
}

void VGA::put_entry(char ch, uint8_t color, size_t r, size_t c) {
	const size_t index = r * (max_column + 1) + c;
	buffer[index] = make_entry(ch, color);
}
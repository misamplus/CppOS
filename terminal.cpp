/**
 * The terminal code
 *
 * @package CppOS
 * @since CppOS 1.0
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014  Misam Saki, misam.ir
 * @author Misam Saki,  http://misam.ir/
 */

#include "include/terminal.h"

Terminal::Terminal() {
	max_row = 24;
	max_column = 79;

	row = 0;
	column = 0;
	color = makeColor(7, 0);
	buffer = (uint16_t*) 0xB8000;
	for ( size_t r = 0; r < max_row; r++ ) {
		for ( size_t c = 0; c < max_column; c++ ) {
			const size_t index = r * max_column + c;
			buffer[index] = makeVgaEntry(' ', color);
		}
	}
	setCursor(0, 0);
}

void Terminal::outb(unsigned short int port, char data) {
	asm("outb %%al, %%dx;" : : "d"(port), "a"(data));
}

void Terminal::setCursor(unsigned short int r, unsigned short int c) {
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

size_t Terminal::strlen(const char* str) {
	size_t ret = 0;
	while (str[ret] != 0) ret++;
	return ret;
}

uint8_t Terminal::makeColor(unsigned short int fg, unsigned short int bg) {
	return fg | bg << 4;
}

uint16_t Terminal::makeVgaEntry(char c, uint8_t color) {
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

/**
 * Black: 0
 * Blue: 1
 * Green: 2
 * Cyan: 3
 * Red: 4
 * Magenta: 5
 * Brown: 6
 * Light Grey: 7
 * Dark Grey: 8
 * Light Blue: 9
 * Light Green: 10
 * Light Cyan: 11
 * Light Red: 12
 * Light Magenta: 13
 * Light Brown: 14
 * White: 15
 */

void Terminal::setColor(uint8_t colorx) {
	color = colorx;
}

void Terminal::putEntry(char ch, uint8_t color, size_t r, size_t c) {
	const size_t index = r * (max_column + 1) + c;
	buffer[index] = makeVgaEntry(ch, color);
}

void Terminal::putChar(char c) {
	if (column > max_column) {
		column = 0;
		row++;
	}
	if (row > max_row) {
		row = max_row;
		int index = 0;
		for (size_t r = 0; r <= max_row; r++) {
			for (size_t c = 0; c <= max_column; c++) {
				if (r == max_row) {
					putEntry(' ', 7, r, c);
				} else {
					buffer[index] = buffer[index + (max_column + 1)];
					index += 1;
				}
			}
		}
	}
	if (c == '\n') {
		column = 0;
		row++;
	} else {
		putEntry(c, color, row, column);
		column++;
	}
	setCursor(row, column);
}

void Terminal::printString(const char* data) {
	size_t len = strlen(data);
	for ( size_t i = 0; i < len; i++ ) putChar(data[i]);
}
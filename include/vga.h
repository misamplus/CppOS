/**
 * The Vga library
 *
 * @package CppOS
 * @since CppOS 1.0
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014  Misam Saki, misam.ir
 * @author Misam Saki,  http://misam.ir/
 */

#include <stddef.h>
#include <stdint.h>

#ifndef TERMINAL_H
#define TERMINAL_H
 
class Vga {
private:
	size_t max_row;
	size_t max_column;

	size_t row;
	size_t column;
	uint8_t color;
	uint16_t* buffer;	

	void outb(unsigned short int, char);
	size_t strlen(const char*);
	uint8_t makeColor(unsigned short int, unsigned short int);
	uint16_t makeEntry(char, uint8_t);
public:
	Vga();
	void setCursor(unsigned short int, unsigned short int);
	void setColor(uint8_t);
	void putEntry(char, uint8_t, size_t, size_t);
	void putChar(char);	
	void printString(const char*);
};

#endif
/**
 * The Terminal code
 *
 * @package CppOS
 * @since CppOS 1.05
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#include "../hardware/vga.cpp"
 
#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal {
private:
public:
	size_t max_row;
	size_t max_column;

	size_t row;
	size_t column;
	uint8_t color;
	uint16_t* buffer;

	Terminal();
};

#endif

Terminal::Terminal() {
	VGA vga = VGA(max_row, max_column, row, column, color, buffer);

	max_row = 24;
	max_column = 79;

	row = 0;
	column = 0;
	color = vga.make_color(7, 0);
	buffer = (uint16_t*) 0xB8000;
	for ( size_t r = 0; r < max_row; r++ ) {
		for ( size_t c = 0; c < max_column; c++ ) {
			const size_t index = r * max_column + c;
			buffer[index] = vga.make_entry(' ', color);
		}
	}
	vga.set_cursor(0, 0);
}
/**
 * The stdio simulation!
 *
 * @package CppOS
 * @since CppOS 1.05
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#include <string.h>

int putchar(char c) {
	extern Terminal terminal;

	VGA vga = VGA(terminal.max_row, terminal.max_column, terminal.row, terminal.column, terminal.color, terminal.buffer);

	if (terminal.column > terminal.max_column) {
		terminal.column = 0;
		terminal.row++;
	}
	if (terminal.row > terminal.max_row) {
		terminal.row = terminal.max_row;
		int index = 0;
		for (size_t r = 0; r <= terminal.max_row; r++) {
			for (size_t c = 0; c <= terminal.max_column; c++) {
				if (r == terminal.max_row) {
					vga.put_entry(' ', 7, r, c);
				} else {
					terminal.buffer[index] = terminal.buffer[index + (terminal.max_column + 1)];
					index += 1;
				}
			}
		}
	}
	if (c == '\n') {
		terminal.column = 0;
		terminal.row++;
	} else {
		vga.put_entry(c, terminal.color, terminal.row, terminal.column);
		terminal.column++;
	}
	vga.set_cursor(terminal.row, terminal.column);
	return 0;
}

int puts(const char* str) {
	size_t len = strlen(str);
	for ( size_t i = 0; i < len; i++ ) putchar(str[i]);
	return len;
}
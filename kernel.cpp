/**
 * The kernel code
 *
 * @package CppOS
 * @since CppOS 1.0
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014  Misam Saki, misam.ir
 * @author Misam Saki,  http://misam.ir/
 */

#include "terminal.cpp"

extern "C" {
	void kernel_main() {
		Vga vga = Terminal();
		vga.printString("Hi, Welcome to CppOS!\n");
		vga.printString("This is a simple operating system kernel that written by c++ language.\n\n");
		vga.setColor(1);
		vga.printString("Architecture: x86 protected mode\n");
		vga.printString("Programm languages: Assembly(NASM), C++(GCC)\n");
		vga.printString("Compliled in: Ubuntu 13.10 i686\n\n");
		vga.setColor(2);
		vga.printString("Author: Misam Saki (misam.ir)\n");
		vga.printString("License: GNU Lesser General Public License v3.0\n");
		vga.printString("Copyright (C) 2014  Misam Saki, misam.ir");
	}
}
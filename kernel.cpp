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
		Terminal terminal = Terminal();
		terminal.printString("Hi, Welcome to CppOS!\n");
		terminal.printString("This is a simple operating system kernel that written by c++ language.\n\n");
		terminal.setColor(1);
		terminal.printString("Architecture: x86 protected mode\n");
		terminal.printString("Programm languages: Assembly(NASM), C++(GCC)\n");
		terminal.printString("Compliled in: Ubuntu 13.10 i686\n\n");
		terminal.setColor(2);
		terminal.printString("Author: Misam Saki (misam.ir)\n");
		terminal.printString("License: GNU Lesser General Public License v3.0\n");
		terminal.printString("Copyright (C) 2014  Misam Saki, misam.ir");
	}
}
/**
 * The kernel code
 *
 * @package CppOS
 * @since CppOS 1.0
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014 Misam Saki, misam.ir
 * @author Misam Saki, http://misam.ir/
 */

#include "module/terminal.cpp"
#include "program/main.cpp"

Terminal terminal;

extern "C" {
	void kernel_main() {
		terminal = Terminal();
		main();
	}
}
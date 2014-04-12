/**
 * The linker code
 *
 * @package CppOS
 * @since CppOS 1.0
 * @license GNU Lesser General Public License v3.0
 * @copyright (C) 2014  Misam Saki, misam.ir
 * @author Misam Saki,  http://misam.ir/
 */

ENTRY(_start)

SECTIONS {
	/* Begin @ 1 MB*/
	. = 1M;

	/* multiboot header -> text */
	.text BLOCK(4K) : ALIGN(4K) {
		*(.multiboot)
		*(.text)
	}

	/* Read only data */
	.rodata BLOCK(4K) : ALIGN(4K) {
		*(.rodata)
	}
	
	/* Read-write data */
	.data BLOCK(4K) : ALIGN(4K) {
		*(.data)
	}
	
	/* Read, write, and stack */
	.bss BLOCK(4K) : ALIGN(4K) {
		sbss = .;
		*(COMMON)
		*(.bss)
		*(.bootstrap_stack)
		ebss = .;
	}
	
	/* Additional Here */
}
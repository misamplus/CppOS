;/**
; * The assembly boot code
; *
; * @package CppOS
; * @since CppOS 1.0
; * @license GNU Lesser General Public License v3.0
; * @copyright (C) 2014 Misam Saki, misam.ir
; * @author Misam Saki, http://misam.ir/
; */

MBALIGN		equ  1<<0
MEMINFO		equ  1<<1
FLAGS		equ  MBALIGN | MEMINFO
MAGIC		equ  0x1BADB002
CHECKSUM	equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bootstrap_stack
align 4
	stack_bottom:
	times 16384 db 0
	stack_top:

section .text
	global _start
	extern kernel_main
_start:
	mov esp, stack_top
	call kernel_main
	cli
.hang:
	hlt
	jmp .hang
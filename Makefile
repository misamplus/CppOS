#/**
# * The Makefile script
# *
# * @package CppOS
# * @since CppOS 1.0
# * @license GNU Lesser General Public License v3.0
# * @copyright (C) 2014 Misam Saki, misam.ir
# * @author Misam Saki, http://misam.ir/
# */

AS = nasm
CC = g++
LD = ld
EM = qemu-system-i386
GR = grub-mkrescue

CFLAGS := -Wextra -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs

all: kernel

kernel: kernel.o boot.o
	$(LD) -T linker.ld -o disk/boot/$@ build/kernel.o build/boot.o

kernel.o: kernel.cpp
	$(CC) -c -I./include -o build/$@ $<

boot.o: boot.asm
	$(AS) -f elf -o build/$@ $<

run: kernel
	$(EM) -kernel disk/boot/$<

iso: kernel
	$(GR) -o iso/CppOS.iso disk

run-iso: iso
	$(EM) iso/CppOS.iso

clean: FRC
	rm -f *.o
	rm -f build/*.o

FRC:
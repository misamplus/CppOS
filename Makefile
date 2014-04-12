all: kernel

kernel: kernel.o boot.o
	ld -T linker.ld -o disk/boot/$@ build/kernel.o build/boot.o

kernel.o: kernel.cpp
	gcc -c -Wall -Wextra -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -o build/$@ $<

boot.o: boot.asm
	nasm -f elf -o build/$@ $<

run: kernel
	qemu -kernel disk/boot/$<

iso: kernel
	grub-mkrescue -o iso/CppOS.iso disk

run-iso: iso
	qemu iso/CppOS.iso

clean: FRC
	rm -f *.o
	rm -f build/*.o

FRC:
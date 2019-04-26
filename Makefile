
all: kernel.o kernel_entry.o kernel.bin bootsect.bin os-image.bin

kernel.bin: kernel_entry.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

kernel_entry.o: boot/kernel_entry.asm
	nasm $< -f elf -o $@

kernel.o: kernel/kernel.c
	i386-elf-gcc -ffreestanding -c $< -o $@

bootsect.bin: boot/bootsect.asm
	nasm $< -f bin -o $@

os-image.bin: bootsect.bin kernel.bin
	cat $^ > $@

run: os-image.bin
	qemu-system-i386 -fda $<

clean:
	rm *.bin *.o 

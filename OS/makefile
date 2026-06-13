CC=gcc
ASM=nasm

CFLAGS=-ffreestanding -m32 -Wall -Wextra -fno-pie
LDFLAGS=-m32 -T linker.ld -ffreestanding -nostdlib -fno-pie -no-pie

C_SOURCES=$(shell find . -name "*.c")
C_OBJECTS=$(C_SOURCES:.c=.o)

ASM_SOURCES=$(shell find . -name "*.asm")
ASM_OBJECTS=$(ASM_SOURCES:.asm=.o)

all: os.iso

os.bin: $(C_OBJECTS) $(ASM_OBJECTS)
	$(CC) $(LDFLAGS) -o os.bin $(C_OBJECTS) $(ASM_OBJECTS) -lgcc

os.iso: os.bin
	mkdir -p iso/boot/grub
	cp os.bin iso/boot/os.bin
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o os.iso iso

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(ASM) -f elf32 $< -o $@

run: os.iso
	qemu-system-i386 -cdrom os.iso

clean:
	rm -f $(C_OBJECTS)
	rm -f $(ASM_OBJECTS)
	rm -f os.bin
	rm -f os.iso

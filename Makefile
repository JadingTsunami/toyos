OBJECTS = loader.o kmain.o display.o io.o string.o serial.o debug.o cpu.o gdt.o interrupts.o interrupts_asm.o pic.o keyboard.o paging.o paging_asm.o
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
         -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	mkisofs -R                              \
          -b boot/grub/stage2_eltorito    \
          -no-emul-boot                   \
          -boot-load-size 4               \
          -A os                           \
          -input-charset utf8             \
          -quiet                          \
          -boot-info-table                \
          -o os.iso                       \
          iso

run: os.iso
	bochs -f bochsrc.txt -q -rc bochscmd.txt

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf *.o kernel.elf os.iso

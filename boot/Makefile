LD = i386-elf-ld
CFLAGS = --target=i386-jos-elf -ffreestanding -m16
CC = gcc
BOOT_IMG = ../boot.img
OUT_BIN = loader.bin

C_SOURCES = $(wildcard *.c)
C_OBJECTS = $(C_SOURCES:.c=.o)

ASM_SOURCES = $(wildcard *.asm)
ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)

$(OUT_BIN): $(C_OBJECTS) boot.bin
	$(LD) -s $(C_OBJECTS) -o $@ -Ttext 0x7e00 --oformat binary
	mcopy -i $(BOOT_IMG) $(OUT_BIN) ::/

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

boot.bin: boot.asm
	nasm $< -o $@
	dd if=$@ of=$(BOOT_IMG) conv=notrunc

run: $(OUT_BIN)
	(cd ../ && docker-compose up -d && docker exec -it centos ./asm/$<)

clean:
	rm -f $(C_OBJECTS) $(ASM_OBJECTS) $(OUT_BIN) *.bin

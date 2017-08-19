LD = i386-elf-ld
CFLAGS = --target=i386-jos-elf -ffreestanding -masm=att -m16
CC = gcc
OUT_BIN = loader.bin

C_SOURCES = $(wildcard *.c)
C_OBJECTS = $(C_SOURCES:.c=.o)

ASM_SOURCES = $(wildcard *.asm)
ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)

$(OUT_BIN): $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) -s $(C_OBJECTS) -o $@ -e _start -Ttext 0xc200 --oformat binary

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm -f elf $< -o $@

run: $(OUT_BIN)
	(cd ../ && docker-compose up -d && docker exec -it centos ./asm/$<)

clean:
	rm -f $(C_OBJECTS) $(ASM_OBJECTS) $(OUT_BIN)

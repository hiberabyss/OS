LD = "i386-elf-ld"
CFLAGS = "--target=i386-jos-elf -ffreestanding"
CC = gcc
OUT_BIN = kernel.bin

C_SOURCES = $(wildcard *.c)
C_OBJECTS = $(C_SOURCES:.c=.o)

ASM_SOURCES = $(wildcard *.asm)
ASM_OBJECTS = $(ASM_SOURCES:.asm=.o)

$(OUT_BIN): $(ASM_OBJECTS) $(C_OBJECTS)
	$(LD) -s $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	nasm -f elf $< -o $@

run: $(OUT_BIN)
	(cd ../ && docker-compose up -d && docker exec -it centos ./asm/$<)

clean:
	rm $(C_OBJECTS) $(ASM_OBJECTS) $(OUT_BIN)

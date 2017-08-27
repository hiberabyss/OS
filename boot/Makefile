include ../env.mk

BOOT_IMG = ../boot.img
LOADER_BIN = loader.bin
LOADER_MEM_START = 0xc000
FAT12_BITMAP_MEM_START = 0xa000

all: boot.bin $(LOADER_BIN)

C_SOURCES = $(wildcard *.c)
C_OBJECTS = $(C_SOURCES:.c=.o)

FONT = ../font/hankaku.o

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(FONT): ../font/
	make -C $<

$(BOOT_IMG):
	@dd if=/dev/zero of=$@ bs=1024 count=1440

$(LOADER_BIN): $(C_OBJECTS) $(FONT) $(BOOT_IMG)
	$(LD) -s $(C_OBJECTS) $(FONT) -o $@ -Ttext $(LOADER_MEM_START) --oformat binary
	mcopy -o -i $(BOOT_IMG) $(LOADER_BIN) ::/

boot.bin: boot.asm $(BOOT_IMG)
	nasm -D LOADER_MEM_START=$(LOADER_MEM_START) $< -o $@
	dd if=$@ of=$(BOOT_IMG) conv=notrunc

run: $(LOADER_BIN)
	(cd ../ && docker-compose up -d && docker exec -it centos ./asm/$<)

clean:
	rm -f $(C_OBJECTS) $(ASM_OBJECTS) $(LOADER_BIN) $(FONT) *.bin

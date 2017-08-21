include ../env.mk

KERNEL_BIN = kernel.bin

all: kernel.o $(KERNEL_BIN)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(KERNEL_BIN): kernel.o
	$(LD) -s $< -o $@ -Ttext 0x10000 --oformat binary
	mcopy -o -i ../boot.img $@ ::/

clean:
	rm -f kernel.o $(KERNEL_BIN)

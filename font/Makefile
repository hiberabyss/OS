include ../env.mk

all: hankaku.o

hankaku.o: ./hankaku.bin
	$(LD) -r -b binary $< -o $@

clean:
	rm -f hankaku.o

all: boot.img hiber.sys

hiber.sys: hiber.asm
	nasm $< -o $@

boot.bin: boot.asm
	nasm $< -o $@

boot.img: boot.bin hiber.sys
	dd if=/dev/zero of=boot.img bs=1024 count=1440
	dd if=$< of=$@ conv=notrunc
	mcopy -i $@ hiber.sys ::/

clean:
	rm hiber.sys boot.bin boot.img

run: boot.img
	qemu-system-i386 -boot order=a -drive file=boot.img,index=0,if=floppy,format=raw

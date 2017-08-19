all: boot.img hiber.sys

hiber.sys: hiber.asm
	nasm $< -o $@

boot.bin: boot.asm
	nasm $< -o $@

boot.img: boot.bin loader/loader.bin
	dd if=/dev/zero of=boot.img bs=1024 count=1440
	dd if=$< of=$@ conv=notrunc
	mcopy -i $@ loader/loader.bin ::/

clean:
	rm hiber.sys boot.bin boot.img

run: boot.img
	qemu-system-i386 -s -boot order=a -drive file=boot.img,index=0,if=floppy,format=raw

gdb: boot.img
	qemu-system-i386 -S -s -boot order=a -drive file=boot.img,index=0,if=floppy,format=raw &
	sudo gdb

kill:
	pkill -f qemu-system-i386

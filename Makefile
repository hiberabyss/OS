SUBDIRS := $(wildcard */)

all: boot.img $(SUBDIRS)

.PHONY: all $(SUBDIRS)

$(SUBDIRS):
	make -C $@

boot.img:
	dd if=/dev/zero of=boot.img bs=1024 count=1440

clean:
	rm -f boot.img
	make -C $(SUBDIRS) clean

run: boot.img
	qemu-system-i386 -s -boot order=a -drive file=boot.img,index=0,if=floppy,format=raw

gdb: boot.img
	pkill -f qemu-system-i386 || true
	qemu-system-i386 -S -s -boot order=a -drive file=boot.img,index=0,if=floppy,format=raw &
	sudo gdb

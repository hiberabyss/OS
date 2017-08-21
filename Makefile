SUBDIRS = boot/ kernel/

BOOT_BIN = boot/boot.bin
LOADER_BIN = boot/loader.bin
KERNEL_BIN = kernel.bin

BOOT_IMG = boot.img

export

all: boot.img $(SUBDIRS)

.PHONY: all $(SUBDIRS)

$(SUBDIRS):
	make -C $@

run: boot.img $(SUBDIRS)
	qemu-system-i386 -s -boot order=a -drive file=$<,index=0,if=floppy,format=raw

gdb: boot.img
	pkill -f qemu-system-i386 || true
	qemu-system-i386 -S -s -boot order=a -drive file=boot.img,index=0,if=floppy,format=raw &
	sudo gdb

clean:
	rm -f boot.img
	echo $(SUBDIRS) | xargs -n1 -I %  make -C % clean

SUBDIRS = boot/ kernel/

BOOT_BIN = boot/boot.bin
LOADER_BIN = boot/loader.bin
KERNEL_BIN = kernel.bin

BOOT_IMG = boot.img

QEMU_FLAGS = -boot order=a -drive file=$(BOOT_IMG),index=0,if=floppy,format=raw 

export

all: $(SUBDIRS)

.PHONY: all $(SUBDIRS)

$(BOOT_IMG): $(SUBDIRS)

$(SUBDIRS):
	make -C $@

run: $(BOOT_IMG) kill
	qemu-system-i386 -s $(QEMU_FLAGS)

gdb: $(BOOT_IMG) kill
	qemu-system-i386 -S -s $(QEMU_FLAGS) &
	sudo gdb

kill:
	pkill -f qemu-system-i386 || true

clean:
	rm -f boot.img
	echo $(SUBDIRS) | xargs -n1 -I %  make -C % clean

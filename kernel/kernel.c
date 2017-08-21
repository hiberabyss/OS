#include "kernel.h"

void _entry() {
	_start();
}

void enter_vga_mode() {
	__asm__ __volatile__ (
			"movb $0x13, %al;"
			"movb $0, %ah;"
			"int $0x10;"
			);

	for (char *p = VGA_ADDR_START; p < VGA_ADDR_END; ++p) {
		*p = 15;
	}
}

void _start() {
}

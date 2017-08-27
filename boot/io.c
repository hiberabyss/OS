#include "io.h"

void io_cli() {
	__asm__ __volatile__ (
			"cli;"
			);
}

void io_out8(int port, int data) {
	__asm__ __volatile__ (
			"mov %0, %%edx;"
			"mov %1, %%al;"
			"out %%al, %%dx;"
			: : "m" (port), "m"(data)
			);
}

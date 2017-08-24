#include "loader.h"

void _start() {
	const char *kernel_name = "KERNEL  BIN";
	for (char *p = FAT12_ROOT_MEM_ADDR_START; p < FAT12_ROOT_MEM_ADDR_END; p += 32) {
		if (IS_NAME_EQUAL(p, kernel_name)) {
			print_string(p);
		}
	}

	FIN();
}

void print_string(const char *str) {
	while(*str) {
		char ch = *str;
		PRINT_CHAR(ch);
		str++;
	}
}

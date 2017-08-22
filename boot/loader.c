#include "loader.h"

void print_string(const char *str) {
	while(*str) {
		char ch = *str;
		PRINT_CHAR(ch);
		str++;
	}
}

char is_name_equal(const char *name1, const char *name2) {
	char res = 1;
	for (int i = 0; i < 11; ++i) {
		if (name1[i] != name2[i]) {
			res = 0;
		}
	}
	return res;
}

void _start() {
	const char *kernel_name = "KERNEL  BIN";
	print_string(kernel_name);
	for (char *p = FAT12_ROOT_MEM_ADDR_START; p < FAT12_ROOT_MEM_ADDR_END; p += 32) {
		if (is_name_equal(p, kernel_name)) {
			print_string(p);
		}
	}

	FIN();
}

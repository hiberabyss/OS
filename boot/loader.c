#include "loader.h"

void print_string(const char *str) {
	while(*str) {
		char ch = *str;
		PRINT_CHAR(ch);
		str++;
	}
}

void init() {
	ENTER_VGA_MODE();
	for (char *p = VGA_MEM_START; p < VGA_MEM_END; ++p) {
		*p = (int)p & 0x0f;
	}
}

// vim:nowrap:

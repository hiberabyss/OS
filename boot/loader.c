#include "loader.h"
#include "graphic.h"

void print_string(const char *str) {
	while(*str) {
		char ch = *str;
		PRINT_CHAR(ch);
		str++;
	}
}

void init() {
	ENTER_VGA_MODE();
	init_palette();

	init_graphic();
}

// vim:nowrap:

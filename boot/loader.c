#include "loader.h"

void _entry() {
	_start();
}

void print_string(const char *str) {
	while(*str) {
		char ch = *str;
		print_char(ch);
		str++;
	}
}

void fin() {
	__asm__ __volatile__ (
			"_fin: hlt\n"
			"jmp _fin\n"
			);
}

void print_char(const char c) {
	__asm__ __volatile__ (
			"movb %0, %%al\n"
			"movb $0xe, %%ah\n"
			"movw $15, %%bx\n"
			"int $0x10\n"
			: : "m" (c)
			);  
}

/* void read_memory(const char *buf_src, char *buf_dest, int len) { */
	/* for (int i = 0; i < len; ++i) { */
		/* buf_dest[i] = buf_src[i]; */
	/* } */
/* } */

void _start() {
	/* char *buf = BUF_START; */
	/* read_memory((char *)0x7c03, buf, 8); */
	/* buf[8] = '\0'; */
	/* print_string(FAT12_TABLE_ADDR); */
	print_string(BOOT_SECTOR_ADDR + 3);

	/* for (char *p = FAT12_TABLE_ADDR; p < FAT12_TABLE_END; p += FAT12_PER_DIR_META_SIZE) { */
		/* const char *loader = "LOADER  BIN"; */
		/* char is_equal = 1; */
		/* for (int i = 0; i < 11; ++i) { */
			/* if (p[i] != loader[i]) { */
				/* is_equal = 0; */
				/* break; */
			/* } */
		/* } */

		/* if (is_equal) { */
			/* print_string(p); */
			/* break; */
		/* } */
	/* } */

	fin();
}

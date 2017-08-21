#include "loader.h"

void _entry() {
	_start();
}

/* void (*asm_fin) () = (void (*)()) ASM_FUNCTIONS; */
/* void (*print_char) (const char) = (void (*)(const char)) (ASM_FUNCTIONS + 1); */

void fin() {
 	__asm__ __volatile__ (
 			"_fin: hlt\n"
 			"jmp _fin\n"
 			);
}

void print_string(const char *str) {
	while(*str) {
		char ch = *str;
		print_char(ch);
		str++;
	}
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
	for (char *p = FAT12_ROOT_MEM_ADDR_START; p < FAT12_ROOT_MEM_ADDR_END; p += 32) {
		if (is_name_equal(p, kernel_name)) {
			print_string(p);
		}
	}

	fin();
}

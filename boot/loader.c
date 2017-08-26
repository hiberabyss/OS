#include "loader.h"

void _start() {
	const char *loader_name = "LOADER  BIN";
	short sect_idx = FIND_FILE_SEC_IDX(loader_name);
	/* sect_idx = 3; */
	PRINT_CHAR(0x30 + sect_idx);
	/* for (char *p = FAT12_ROOT_MEM_ADDR_START; p < FAT12_ROOT_MEM_ADDR_END; p += 32) { */
		/* if (IS_NAME_EQUAL(p, kernel_name)) { */
			/* print_string(p); */
		/* } */
	/* } */
}

void print_string(const char *str) {
	while(*str) {
		char ch = *str;
		PRINT_CHAR(ch);
		str++;
	}
}

#include "loader.h"

// entrypoint
void _entry() {
	_start();
}

uint16 find_next_sect_idx(uint16 sect_idx) {
	uint16 byte_idx = sect_idx + (sect_idx/2);
	const uint8 *entry = &FAT12_BITMAP_MEM_START[byte_idx];

	uint16 res = 0;
	if (sect_idx % 2) {
		res += BYTE_HIGH(entry[0]) + (entry[1] << 4);
	} else {
		res = entry[0] + (BYTE_LOW(entry[1]) << 8);
	}

	return res;
}

void _start() {
	// read loader
	uint16 loader_sect_idx = ASM_VARIABLE[0];
	int load_mem_adr = (int) LOADER_MEM_START;

	for (uint16 idx = find_next_sect_idx(loader_sect_idx); idx < FAT12_BITMAP_MAX; idx = find_next_sect_idx(idx)) {
		load_mem_adr += FAT12_SECTOR_SIZE;
		READ_ONE_SECT(idx + 31, (load_mem_adr / 16), (load_mem_adr % 16));
		PRINT_CHAR('.');
	}

	print_string("\r\nloader has been loaded!");
	init();
	FIN();
}


#ifndef LOADER_H
#define LOADER_H

#define FAT12_SECTOR_SIZE 512
#define FAT12_FIRST_CLUSTER_IDX 2
#define FAT12_FIRST_DATA_CLUSTER 33
#define BUF_START (char *)0x7f00
#define BOOT_SECTOR_ADDR (char *)0x7c00
#define FAT12_TABLE_ADDR (char *)0xa600
#define FAT12_TABLE_END (9 * FAT12_SECTOR_SIZE + FAT12_TABLE_ADDR)
#define FAT12_PER_DIR_META_SIZE 32

#define FAT12_BITMAP_MEM_START (char *)0xa000

#define FAT12_ROOT_MEM_ADDR_START (char *) 0x8000
#define FAT12_ROOT_MEM_ADDR_END (char *) (0x8000 + 14 * 512)

// typedef void fin();
#define ASM_FUNCTIONS ((void **)0x7e00)
#define FIN ((void (*) ()) ASM_FUNCTIONS[0])
#define PRINT_CHAR ((void (*) (const char)) (ASM_FUNCTIONS[1]))
#define IS_NAME_EQUAL ((char (*) (const char *, const char *)) (ASM_FUNCTIONS[2]))
#define FIND_FILE_SEC_IDX ((short (*) (const char *)) (ASM_FUNCTIONS[3]))

void _start();
void print_string(const char *str);

// entrypoint
void _entry() {
	_start();
	FIN();
}

#endif /* end of include guard: LOADER_H */


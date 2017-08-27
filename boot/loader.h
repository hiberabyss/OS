#ifndef LOADER_H
#define LOADER_H

#define LOADER_MEM_START ((char *)0xc000)

#define FAT12_BITMAP_MAX 0xff8

#define FAT12_SECTOR_SIZE 512
#define FAT12_FIRST_CLUSTER_IDX 2
#define FAT12_FIRST_DATA_CLUSTER 33
#define BUF_START ((char *)0x7f00)
#define BOOT_SECTOR_ADDR ((unsigned char *)0x7c00)
#define FAT12_TABLE_ADDR ((unsigned char *)0xa600)
#define FAT12_TABLE_END (9 * FAT12_SECTOR_SIZE + FAT12_TABLE_ADDR)
#define FAT12_PER_DIR_META_SIZE 32

#define BYTE_HIGH(a) (((unsigned char)a) >> 4)
#define BYTE_LOW(a) (((unsigned char)a) & 0x0f)

typedef unsigned short int uint16;
typedef unsigned char uint8;

#define FAT12_BITMAP_MEM_START ((unsigned char *)0xa000)

#define FAT12_ROOT_MEM_ADDR_START (char *) 0x8000
#define FAT12_ROOT_MEM_ADDR_END (char *) (0x8000 + 14 * 512)

#define VGA_MEM_START ((char *) 0xa0000)
#define VGA_MEM_END ((char *) 0xb0000)

#define ASM_FUNCTIONS ((void **)0x7e00)
#define ASM_VARIABLE ((unsigned short int *)0x7f00)

#define FIN ((void (*) ()) ASM_FUNCTIONS[0]) // 0x7c89
#define PRINT_CHAR ((void (*) (const char)) (ASM_FUNCTIONS[1]))
#define IS_NAME_EQUAL ((char (*) (const char *, const char *)) (ASM_FUNCTIONS[2]))
#define FIND_FILE_SEC_IDX ((short (*) (const char *)) (ASM_FUNCTIONS[3]))
#define READ_ONE_SECT ((void (*) (uint16, uint16, uint16)) (ASM_FUNCTIONS[4]))
#define ENTER_VGA_MODE ((void (*) ()) (ASM_FUNCTIONS[5]))

void _start();
void print_string(const char *str);
uint16 find_next_sect_idx(uint16 sect_idx);
void init();

#endif /* end of include guard: LOADER_H */

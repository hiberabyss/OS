#define FAT12_SECTOR_SIZE 512
#define FAT12_FIRST_CLUSTER_IDX 2
#define FAT12_FIRST_DATA_CLUSTER 33
#define BUF_START (char *)0x7f00
#define BOOT_SECTOR_ADDR (char *)0x7c00
#define FAT12_TABLE_ADDR (char *)0xa600
#define FAT12_TABLE_END (9 * FAT12_SECTOR_SIZE + FAT12_TABLE_ADDR)
#define FAT12_PER_DIR_META_SIZE 32

void _start();
void print_char(const char c);
void fin();
void print_string(const char *str);


#include "io.h"
#include "graphic.h"
#include <stdio.h>

void init_palette(void) {
	static unsigned char table_rgb[16 * 3] = {
		0x00, 0x00, 0x00,	/*  0:黑 */
		0xff, 0x00, 0x00,	/*  1:梁红 */
		0x00, 0xff, 0x00,	/*  2:亮绿 */
		0xff, 0xff, 0x00,	/*  3:亮黄 */
		0x00, 0x00, 0xff,	/*  4:亮蓝 */
		0xff, 0x00, 0xff,	/*  5:亮紫 */
		0x00, 0xff, 0xff,	/*  6:浅亮蓝 */
		0xff, 0xff, 0xff,	/*  7:白 */
		0xc6, 0xc6, 0xc6,	/*  8:亮灰 */
		0x84, 0x00, 0x00,	/*  9:暗红 */
		0x00, 0x84, 0x00,	/* 10:暗绿 */
		0x84, 0x84, 0x00,	/* 11:暗黄 */
		0x00, 0x00, 0x84,	/* 12:暗青 */
		0x84, 0x00, 0x84,	/* 13:暗紫 */
		0x00, 0x84, 0x84,	/* 14:浅暗蓝 */
		0x84, 0x84, 0x84	/* 15:暗灰 */
	};
	set_palette(0, 15, table_rgb);
	return;
}

void set_palette(int start, int end, unsigned char *rgb) {
	int eflags = IO_SAVE_EFLAGS();
	io_cli();
	io_out8(0x03c8, start);
	for (int i = start; i <= end; i++) {
		io_out8(0x03c9, rgb[0] / 4);
		io_out8(0x03c9, rgb[1] / 4);
		io_out8(0x03c9, rgb[2] / 4);
		rgb += 3;
	}
	IO_RESTORE_EFLAGS(eflags);
	return;
}

void boxfill(unsigned char color, int x0, int y0, int x1, int y1) {
	unsigned char *vram = (unsigned char *)VGA_MEM_START;

	for (int i = y0; i <= y1; ++i) {
		for (int j = x0; j <= x1; ++j) {
			vram[i * XSIZE + j] = color;
		}
	}

	return;
}

void putfont8(int x, int y, char c, char *font) {
	for (int i = 0; i < 16; i++) {
		char *p = VGA_MEM_START + (y + i) * XSIZE + x;
		unsigned char d = font[i];
		/* unsigned char ch = ((d & 0x0f) << 4) + ((d & 0xf0) >> 4); */
		for (int j = 0; j < 8; ++j) {
			if ( (d & (1 << j)) ) {
				p[7-j] = c;
			}
		}
	}
	return;
}

void put_string(int x, int y, char color, char *str) {
	while (*str) {
		putfont8(x, y, color, _binary_hankaku_bin_start + (*str) * 16);
		x += 8;
		str++;
	}
}

void init_screen() {
	int xsize = 320, ysize = 200;

	boxfill(COL8_008484,  0,         0,          xsize -  1, ysize - 29);
	boxfill(COL8_C6C6C6,  0,         ysize - 28, xsize -  1, ysize - 28);
	boxfill(COL8_FFFFFF,  0,         ysize - 27, xsize -  1, ysize - 27);
	boxfill(COL8_C6C6C6,  0,         ysize - 26, xsize -  1, ysize -  1);

	boxfill(COL8_FFFFFF,  3,         ysize - 24, 59,         ysize - 24);
	boxfill(COL8_FFFFFF,  2,         ysize - 24,  2,         ysize -  4);
	boxfill(COL8_848484,  3,         ysize -  4, 59,         ysize -  4);
	boxfill(COL8_848484, 59,         ysize - 23, 59,         ysize -  5);
	boxfill(COL8_000000,  2,         ysize -  3, 59,         ysize -  3);
	boxfill(COL8_000000, 60,         ysize - 24, 60,         ysize -  3);

	boxfill(COL8_848484, xsize - 47, ysize - 24, xsize -  4, ysize - 24);
	boxfill(COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize -  4);
	boxfill(COL8_FFFFFF, xsize - 47, ysize -  3, xsize -  4, ysize -  3);
	boxfill(COL8_FFFFFF, xsize -  3, ysize - 24, xsize -  3, ysize -  3);

	/* sprintf(buf, "screen: %d", 320); */
	put_string(8, 8, COL8_FFFFFF, "ABC, 123!");
}

void init_mouse_cursor8(char *mouse, char bc) {
	static char cursor[16][16] = {
		"**************..",
		"*OOOOOOOOOOO*...",
		"*OOOOOOOOOO*....",
		"*OOOOOOOOO*.....",
		"*OOOOOOOO*......",
		"*OOOOOOO*.......",
		"*OOOOOOO*.......",
		"*OOOOOOOO*......",
		"*OOOO**OOO*.....",
		"*OOO*..*OOO*....",
		"*OO*....*OOO*...",
		"*O*......*OOO*..",
		"**........*OOO*.",
		"*..........*OOO*",
		"............*OO*",
		".............***"
	};
	int x, y;

	for (y = 0; y < 16; y++) {
		for (x = 0; x < 16; x++) {
			if (cursor[y][x] == '*') {
				mouse[y * 16 + x] = COL8_000000;
			}
			if (cursor[y][x] == 'O') {
				mouse[y * 16 + x] = COL8_FFFFFF;
			}
			if (cursor[y][x] == '.') {
				mouse[y * 16 + x] = bc;
			}
		}
	}
	return;
}

void putblock8_8(int pxsize,
	int pysize, int px0, int py0, char *buf, int bxsize) {
	int x, y;
	for (y = 0; y < pysize; y++) {
		for (x = 0; x < pxsize; x++) {
			VGA_MEM_START[(py0 + y) * XSIZE + (px0 + x)] = buf[y * bxsize + x];
		}
	}
	return;
}

void init_mouse() {
	char mcursor[256];
	int mx = (XSIZE - 16) / 2;
	int my = (YSIZE - 28 - 16) / 2;
	init_mouse_cursor8(mcursor, COL8_008484);
	putblock8_8(16, 16, mx, my, mcursor, 16);
}

void init_graphic() {
	init_screen();
	init_mouse();
}

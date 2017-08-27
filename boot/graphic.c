#include "io.h"
#include "graphic.h"


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

void putfont8(int x, int y, char c, char *font)
{
	for (int i = 0; i < 16; i++) {
		char *p = VGA_MEM_START + (y + i) * XSIZE + x;
		char d = font[i];
		if ((d & 0x80) != 0) { p[0] = c; }
		if ((d & 0x40) != 0) { p[1] = c; }
		if ((d & 0x20) != 0) { p[2] = c; }
		if ((d & 0x10) != 0) { p[3] = c; }
		if ((d & 0x08) != 0) { p[4] = c; }
		if ((d & 0x04) != 0) { p[5] = c; }
		if ((d & 0x02) != 0) { p[6] = c; }
		if ((d & 0x01) != 0) { p[7] = c; }
	}
	return;
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

	putfont8(8, 8, COL8_FFFFFF, _binary_hankaku_bin_start + 'A' * 16);
}

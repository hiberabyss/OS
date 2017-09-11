#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "loader.h"

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);
void boxfill(unsigned char color, int x0, int y0, int x1, int y1);
void init_screen();
void init_graphic();
extern char _binary_hankaku_bin_start[4096];

#define XSIZE 320
#define YSIZE 200

#define COL8_000000		0
#define COL8_FF0000		1
#define COL8_00FF00		2
#define COL8_FFFF00		3
#define COL8_0000FF		4
#define COL8_FF00FF		5
#define COL8_00FFFF		6
#define COL8_FFFFFF		7
#define COL8_C6C6C6		8
#define COL8_840000		9
#define COL8_008400		10
#define COL8_848400		11
#define COL8_000084		12
#define COL8_840084		13
#define COL8_008484		14
#define COL8_848484		15

#endif /* end of include guard: GRAPHIC_H */



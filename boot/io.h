#ifndef IO_H
#define IO_H

#include "loader.h"

#define IO_SAVE_EFLAGS ((int (*) ()) (ASM_FUNCTIONS[6]))
#define IO_RESTORE_EFLAGS ((void (*) (int)) (ASM_FUNCTIONS[7]))
void io_cli();
void io_out8(int port, int data);

#endif /* end of include guard: IO_H */


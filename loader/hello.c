/* void myprint(const char *msg); */

/* void fin() { */
	/* __asm__ __volatile__ ( */
			/* "_fin: hlt\n" */
			/* "jmp _fin\n" */
			/* ); */
/* } */

void print_char(const char c);
void fin();

void _start() {
	print_char('I');
	fin();
}

void fin() {
	__asm__ __volatile__ (
			"_fin: hlt\n"
			"jmp _fin\n"
			);
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


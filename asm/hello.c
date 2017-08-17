void myprint(const char *msg, int len);

int choose(int a, int b) {
	if (a > b) myprint("choose the first one!\n", 23);
	else myprint("choose the second one!\n", 24);

	return 0;
}

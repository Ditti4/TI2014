#include <stdio.h>

main() {
	char hw[13]="Hello World!";
	int i = 0;
	for (i = 0; i < 12; i++) {
		putchar(hw[i]);
	}

	return 1;
}
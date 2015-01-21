#include <stdio.h>
#include <math.h>

#define print(__string) for(__i=0; __string[__i] != '\0'; __i++) putchar(__string[__i]);
#define pi 3.141593
int __i;

void div(int n) {
	if (n / 2 != 0)
		div(n / 2);
	putchar((n % 2)+ 48);
}

main() {
	int n;
	print("n =\t\t")
		scanf("%d", &n);
	div(n);
	putchar('\n');
	return 0;
}

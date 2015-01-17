#include <stdio.h>
#include <math.h>

#define print(__string) for(__i=0; __string[__i] != '\0'; __i++) putchar(__string[__i]);
#define pi 3.141593
int __i;

int fibo(int n) {
	if (n <= 0)
		return -1;
	if (n == 1 || n == 2)
		return 1;
	return (fibo(n - 1) + fibo(n - 2));
}

main() {
	int n;
	print("Anzahl der Rechenschritte:\t");
	scanf("%d", &n);
	printf("f(%d) = \t\t\t%d\n\n", n, fibo(n));
	return 0;
}

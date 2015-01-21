#include <stdio.h>
#define print(__string) for(__i=0; __string[__i] != '\0'; __i++) putchar(__string[__i]);
int __i;

int main() {
	int numbers[10], max = -32768, min = 32767, i = 0, maxcount = 0, mincount = 0, smincount = 0, smaxcount = 0;
	print("Maximum- und Minimumbstimmung\n");

	for (i = 0; i < 10; i++) {
		printf("%d. Zahl eingeben:\t", i + 1);
		scanf("%d", &numbers[i]);
	}
	for (i = 0; i < 10; i++) {
		if (min == numbers[i])
			smincount++;
		if (max == numbers[i])
			smaxcount++;
		if (numbers[i] > max) {
			max = numbers[i];
			smaxcount = 1;
			maxcount++;
		}
		if (numbers[i] < min) {
			min = numbers[i];
			smincount = 1;
			mincount++;
		}
	}

	printf("------------------\nDas Maximum ist\t\t%d\t\tmaxcount = %d\nDas Minimum ist\t\t%d\t\tmincount = %d\n", max, maxcount, min, mincount);
	printf("\t\t\t\t\tsmincount = %d\n\t\t\t\t\tsmaxcount = %d\n", smincount, smaxcount);
}

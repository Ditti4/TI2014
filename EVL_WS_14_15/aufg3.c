#include <stdio.h>

void main() {
    int a[4] = {1, 3, 5, 7}, b[4] = {8, 6, 4, 2}, c[8];
    int i, tmp, exchange;

    for(i = 0; i < 4; i++)
        c[i] = a[i];
    for(i = 0; i < 4; i++)
        c[i + 4] = b[i];
    do{
        exchange = 0;
        for (i = 0; i < 7; i++) {
            if (c[i] > c[i + 1]) {
                tmp = c[i];
                c[i] = c[i + 1];
                c[i + 1] = tmp;
                exchange++;
            }
        }
    } while (exchange != 0);
    printf("Here, take this!\n");
    for (i = 0; i < 8; i++)
        printf("%d ", c[i]);
    putchar('\n');
}

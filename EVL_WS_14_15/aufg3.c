#include <stdio.h>
#include <stdlib.h>

void main() {
    int *a, *b, *c;
    int i, tmp, exchange, x = 0, y = 0;

    a = malloc(sizeof(int));
    b = malloc(sizeof(int));
    
    printf("Zahlen fuer erstes Array eingeben (irgendwas anderes eingeben zum Beenden): ");
    while(1) {
        if(!scanf(" %d", &tmp))
            break;
        x++;
        a = realloc(a, x * sizeof(int));
        *(a + x - 1) = tmp;
    }
    fflush(stdin);
    printf("Zahlen fuer zweites Array eingeben (irgendwas anderes eingeben zum Beenden): ");
    while(1) {
        if(!scanf(" %d", &tmp))
            break;
        y++;
        b = realloc(b, y * sizeof(int));
        *(b + y) = tmp;
    }
    
    c = malloc((x + y) * sizeof(int));

    for(i = 0; i < x; i++)
        *(c + i) = *(a + i);
    for(i = 0; i < y; i++)
        *(c + i + 4) = *(b + i);
    do{
        exchange = 0;
        for (i = 0; i < 7; i++) {
            if (*(c + i) > *(c + i + 1)) {
                tmp = *(c + i);
                *(c + i) = *(c + i + 1);
                *(c + i + 1) = tmp;
                exchange++;
            }
        }
    } while (exchange != 0);
    printf("Here, take this!\n");
    for (i = 0; i < 8; i++)
        printf("%d ", c[i]);
    putchar('\n');
}

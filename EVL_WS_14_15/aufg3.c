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
    getchar();
    printf("Zahlen fuer zweites Array eingeben (irgendwas anderes eingeben zum Beenden): ");
    while(1) {
        if(!scanf(" %d", &tmp))
            break;
        y++;
        b = realloc(b, y * sizeof(int));
        *(b + y - 1) = tmp;
    }
    
    c = malloc((x + y) * sizeof(int));

    for(i = 0; i < x; i++)
        *(c + i) = *(a + i);
    for(i = 0; i < y; i++)
        *(c + i + x) = *(b + i);
    do{
        exchange = 0;
        for (i = 0; i < (x + y - 1); i++) {
            if (*(c + i) > *(c + i + 1)) {
                tmp = *(c + i);
                *(c + i) = *(c + i + 1);
                *(c + i + 1) = tmp;
                exchange++;
            }
        }
    } while (exchange != 0);
    for(i = 0; i < (x + y - 1); i++)
        if(*(c + i) > *(c + i + 1))
            printf("Falsch sortierte Zahlen an Stelle %d und %d (%d, %d)\n", i, i + 1, *(c + i), *(c + i + 1));
    printf("Endergebnis nach Versuch der Sortierung:\n");
    for(i = 0; i < (x + y); i++)
        printf("%d ", *(c + i));
    putchar('\n');
}

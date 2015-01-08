#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *outputFile;
    int wert;
    char menu;
    
    printf("Alte Daten (l)oeschen, neue Daten (h)inzufuegen: ");
    menu = getchar();
    fflush(stdin);
    switch(menu) {
        case 'l':
        case 'L':
            remove("daten.txt");
            break;
        case 'h':
        case 'H':
            outputFile = fopen("daten.txt", "a");
            while(1) {
                printf("Wert eingeben: ");
                if(!scanf("%d", &wert))
                    break;
                fflush(stdin);
                fprintf(outputFile, "%d\n", wert);
            }
            break;
    }
    
    fclose(outputFile);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile;
    int *values = malloc(sizeof(int)), i = 0;
    char blub[50];
    
    if((inputFile = fopen("daten.txt", "r"))) {
        while(fgets(blub, 50, inputFile)) {
            values = realloc(values, (i + 1) * sizeof(int));
            sscanf(blub, "%d", (values+i));
            printf("%d\n", *(values+i));
            i++;
        }
        
    } else {
        printf("Datei existiert nicht. Bitte vorher Werte eintragen.");
    }
    
    return 0;
}

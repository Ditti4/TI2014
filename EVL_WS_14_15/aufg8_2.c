#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *inputFile;
    int *values, i, elementcount = 0;
    double x0, x1, f0, f1, area = 0;
    char blub[50];
    
    if((inputFile = fopen("daten.txt", "r"))) {
        while(fgets(blub, 50, inputFile)) {
            values = realloc(values, (elementcount + 1) * sizeof(int));
            sscanf(blub, "%d", (values + elementcount));
            elementcount++;
        }
        for(i = 1; i < elementcount; i++) {
            x0 = 1.0 * (i - 1);
            x1 = 1.0 * i;
            f0 = 1.0 * *(values + i - 1);
            f1 = 1.0 * *(values + i);
            area += f0*x1+((f0-f1)*x1*x1)/(2*(x0-x1))-((f0-f1)*x1*x0)/(x0-x1);
            area -= f0*x0+((f0-f1)*x0*x0)/(2*(x0-x1))-((f0-f1)*x0*x0)/(x0-x1);
        }
        printf("Flaeche: %f\n", area);
    } else {
        printf("Datei existiert nicht. Bitte vorher Werte eintragen.");
        return 1;
    }
    
    return 0;
}

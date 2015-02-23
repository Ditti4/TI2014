#include <stdio.h>

void analyze(unsigned char *string) {
    int max = 0, min = 255, currentword = 0, wordcount = 0, i;

    for(i = 0; i < 256; i++) {
        if(string[i] == ' ' || string[i] == '\0') {
            if(currentword) {
                wordcount++;
                if(currentword < min) {
                    min = currentword;
                }
                if(currentword > max) {
                    max = currentword;
                }
                currentword = 0;
            }
        } else {
            currentword++;
        }
        if(string[i] == '\0') {
            break;
        }
    }
    printf("Anzahl der Woerter: %d\nLaengstes Wort: %d\nKuerzestes Wort: %d\n", wordcount, max, min);
}

void main() {
    unsigned char string[256];

    gets(string);
    analyze(string);
}
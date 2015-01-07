#include <stdio.h>

void analyze(char *string) {
    int max = 0, min = 255, space = -1, i, counter = 0;

    for(i = 0; i < 256 && string[i - 1] != '\0'; i++) {
        if(string[i] == ' ') {
            if(i - 1 >= 0 && string[i - 1] != ' ' )
	        counter++;
            if(i - space + 1 < min) {
                min = i - space + 1;
            } else if(i - space + 1) {
                max = i - space + 1;
            }
            space = i;
        } else if(i + 1 >= 256 || string[i] == '\0'){
            counter++;
            if(i - space + 1 < min) {
                min = i - space + 1;
            } else if(i - space + 1) {
                max = i - space + 1;
            }
        }
        if(i + 1 < 256 && string[i + 1] == ' ' && string[i] == ' ') {
            space = ++i;
        }
    }
    printf("Anzahl der Woerter: %d\nLaengstes Wort: %d\nKuerzestes Wort: %d\n", counter, max, min);
}

void main() {
    char string[256];

    gets(string);
    analyze(string);
}
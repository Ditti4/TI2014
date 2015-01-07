#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    char string[4];
    int i;
    do {
        putchar('?');
        putchar(' ');
        gets(string);
        fflush(stdin);
        for(i = 0; i < 4; i++) {
			if(string[i] >= 65 && string[i] <= 65 + 26)
				string[i] += 32;
		}
		string[3] = '\0';
        if(!strcmp(string, "mon")) {
            printf(" --> Monday\n\n");
        } else if(!strcmp(string, "die")) {
            printf(" --> Tuesday\n\n");
        } else if(!strcmp(string, "mit")) {
            printf(" --> Wednesdays\n\n");
        } else if(!strcmp(string, "don")) {
            printf(" --> Thursday\n\n");
        } else if(!strcmp(string, "fre")) {
            printf(" --> Friday\n\n");
        } else if(!strcmp(string, "sam")) {
            printf(" --> Saturday\n\n");
        } else if(!strcmp(string, "son")) {
            printf(" --> Sunday\n\n");
        } else if(string[0] == '#') {
            continue;
        } else {
            printf(" --> No_day\n\n");
        }
    } while(string[0] != '#');
}

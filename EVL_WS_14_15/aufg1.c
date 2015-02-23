#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replaceLetters(unsigned char *input, unsigned char *output);
int utf8strlen(unsigned char *string);

int main() {
    unsigned char read[257];
    unsigned char out[257];

    gets(read);
    if(utf8strlen(read) > 128) {
        printf("Zeichenkette ist zu lang. Maximallaenge ist 128 Zeichen.\n");
        return 0;
    }
    replaceLetters(read, out);
    printf("Verarbeiteter Text:\n%s\n", out);
}

void replaceLetters(unsigned char *input, unsigned char *output) {
    strcpy(output, input);
    int i;
    for(i = 0; i < 257 && output[i] != '\0'; i++) {
        if(output[i] >= 97 && output[i] <= 97 + 26) {
            output[i] -= 32;
        }
        if(output[i] == 195) {
            switch(output[i + 1]) {
                case 132:
                case 164:
                    output[i] = 'A';
                    output[++i] = 'E';
                    break;
                case 150:
                case 182:
                    output[i] = 'O';
                    output[++i] = 'E';
                    break;
                case 156:
                case 188:
                    output[i] = 'U';
                    output[++i] = 'E';
                    break;
                case 159:
                    output[i] = 'S';
                    output[++i] = 'Z';
                    break;
            }
        }
    }
}

int utf8strlen(unsigned char *string) {
    int i = 0, counter = 0;
    while(string[i] != '\0') {
        if(string[i] == 195) {
            i++;
        } else {
            counter++;
            i++;
        }
    }
    return counter;
}
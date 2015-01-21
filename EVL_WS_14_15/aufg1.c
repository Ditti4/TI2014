#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replaceLetters(unsigned char *input, unsigned char *output);

int main() {
    unsigned char acRead[257];
    unsigned char acOut[257];

    gets(acRead);
    replaceLetters(acRead, acOut);
    printf("Verarbeiteter Text:\n%s\n", acOut);
}

void replaceLetters(unsigned char *input, unsigned char *output) {
    strcpy(output, input);
    int i;
    for(i = 0; i < 257 && output[i] != '\0'; i++) {
        if(output[i] >= 97 && output[i] <= 97 + 26) {
	        output[i] -= 32;
		} else {
            if(output[i] = 195) {
                switch(output[i + 1]) {
                    case 164:
                        output[i + 1] = 132;
                        break;
                    case 182:
                        output[i + 1] = 150;
                        break;
                    case 188:
                        output[i + 1] = 156;
                        break;
                }
            }
        }
		if(output[i] == 195) {
        	switch(output[i + 1]) {
				case 132:
		      		output[i] = 'A';
              		output[++i] = 'E';
              		break;
				case 150:
                	output[i] = 'O';
                	output[++i] = 'E';
                	break;
                case 156:
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void replaceLetters(unsigned char *input, unsigned char *output);
void rightShiftArray(unsigned char *input, int size, int pos);

int main() {
    unsigned char acRead[129];
    unsigned char acOut[257];

    gets(acRead);
    replaceLetters(acRead, acOut);

    printf("Verarbeiteter Text:\n%s\n", acOut);
}

void rightShiftArray(unsigned char *input, int size, int pos) {
    int k;
    for(k = size - 2; k >= pos; k--) {
        input[k + 1] = input[k];
    }
}

void replaceLetters(unsigned char *input, unsigned char *output) {
    strcpy(output, input);
    int i;
    for(i = 0; i < 257 && output[i] != '\0'; i++) {
        if(output[i] >= 97 && output[i] <= 97 + 26) {
	        output[i] -= 32;
		} else {
            switch(output[i]) {
                case 132:
                    output[i] = 142;
                    break;
                case 148:
                    output[i] = 153;
                    break;
                case 129:
                    output[i] = 154;
                    break;
            }
        }
		if(output[i] == 142 || output[i] == 153 || output[i] == 154 || output[i] == 225) {
            rightShiftArray(output, 257, i);
        	switch(output[i]) {
				case 142:
		      		output[i] = 'A';
              		output[++i] = 'E';
              		break;
				case 153:
                	output[i] = 'O';
                	output[++i] = 'E';
                	break;
                case 154:
                    output[i] = 'U';
                    output[++i] = 'E';
                    break;
                case 225:
                    output[i] = 'S';
                    output[++i] = 'Z';
                    break;
            }
        }
    }
}

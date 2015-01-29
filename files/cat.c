#include <stdio.h>
#include <stdlib.h>

void print(char *message) {
    int i = 0;
    while(message[i] != '\0') {
        if(message[i] == '\n')
            break;
        putchar(message[i]);
        i++;
    }
}

void help(char *programname) {
    printf("usage: %s [-En] filename.\n", programname);
}

int main(int argc, char **argv) {
    int filenameindex = 0;
    int flagcombo = 0;
    switch(argc) {
        case 1:
            help(argv[0]);
            return 1;
        case 2:
            if(argv[1][0] == '-') {
                help(argv[0]);
                return 1;
            }
            filenameindex = 1;
            break;
        case 3:
            if(argv[1][0] != '-' || argv[2][0] == '-') {
                help(argv[0]);
                return 1;
            }
            switch(argv[1][1]) {
                case 'E':
                    flagcombo += 1;
                    break;
                case 'n':
                    flagcombo += 2;
                    break;
                default:
                    help(argv[0]);
                    break;
            }
            filenameindex = 2;
            break;
        case 4:
            if(argv[1][0] != '-' || argv[2][0] != '-' || argv[3][0] == '-') {
                help(argv[0]);
                return 1;
            }
            switch(argv[1][1]) {
                case 'E':
                    flagcombo += 1;
                    break;
                case 'n':
                    flagcombo += 2;
                    break;
                default:
                    help(argv[0]);
                    break;
            }
            switch(argv[2][1]) {
                case 'E':
                    if(flagcombo == 2) {
                        flagcombo += 1;
                    } else {
                        help(argv[0]);
                        return 1;
                    }
                    break;
                case 'n':
                    if(flagcombo == 1) {
                        flagcombo += 2;
                    } else {
                        help(argv[0]);
                        return 1;
                    }
                    break;
                default:
                    help(argv[0]);
                    break;
            }
            filenameindex = 3;
            break;
    }
    FILE *fp;
    if(!(fp = fopen(argv[filenameindex], "r"))) {
        printf("%s: file not found\n", argv[0]);
        return 1;
    }
    int i = 1;
    char line[1024];
    while(fgets(line, 1024, fp)) {
        if(flagcombo == 2 || flagcombo == 3)
            printf("%d\t", i++);
        print(line);
        if(flagcombo == 1 || flagcombo == 3)
            putchar('$');
        putchar('\n');        
    }    
    return 0;
}
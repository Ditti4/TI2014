#include <stdio.h>
#include <stdbool.h>

int main(int argc, char **argv) {
    if(argc < 2) {
        printf("usage: %s string_to_check\n", argv[0]);
        return 1;
    }
    char *checkme = argv[1];
    int i = 0;
    bool correctParity = 0;
    while(1) {
        if(!checkme[i])
            break;
        putchar(checkme[i]);
        if(checkme[i] == '1')
            correctParity = !correctParity;
        else if(checkme[i] == '|') {
            if(!correctParity) {
                printf("\nError!");
                break;
            }
            correctParity = false;
        }
        i++;
    }
    putchar('\n');
    return 0;
}

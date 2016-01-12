#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if(argc < 2)
        return 1;

    int len = strlen(argv[1]), i, palindrome = 1;
    for(i = 0; i < (len + (len % 2) / 2); i++) {
        if(argv[1][i] != argv[1][(len - 1) - i]) {
            palindrome = 0;
            break;
        }
    }

    printf("%s ist%sein Palindrom.\n", argv[1], palindrome ? " " : " k");

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

void print_fact(int input) {
    int i;
    for(i = 2; i <= input; i++) {
        if(input % i == 0) {
            printf(" * %d", i);
            return print_fact(input / i);
        }
    }
}

int main(int argc, char **argv) {
    if(argc <= 1) {
        printf("usage: %s numer_to_process\n", argv[0]);
        return 1;
    }
    int input = atoi(argv[1]);
    int i;
    putchar('1');
    print_fact(input);
    putchar('\n');
    return 0;
}

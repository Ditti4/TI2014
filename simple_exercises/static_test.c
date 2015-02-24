#include <stdio.h>

void f() {
    static counter = 1;
    printf("Call #%d\n", counter++);
}

int main(int argc, char **argv) {
    int i;
    for(i = 0; i < 5; i++) f();
    return 0;
}

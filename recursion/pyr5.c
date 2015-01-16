#include <stdio.h>
#define print(string) for(__i=0; string[__i] != '\0'; __i++) putchar(string[__i]);
int __i;

prup(int n) {
    if(n>=1) {
        prup(n-1);
        int i;
        for(i=1; i<=n; i++)
            printf("%d", i);
        putchar('\n');
    }
}

prdown(int n) {
    if(n>=1) {
        int i;
        for(i=1; i<=n; i++)
            printf("%d", i);
        putchar('\n');
        prdown(n-1);
    }
}

printSequenz(int n) {
    if(n>=1) {
        prup(n-1);
        prdown(n);
    }
}

main() {
    int number;
    print("Give number! ");
    scanf("%d", &number);
    printSequenz(number);
}

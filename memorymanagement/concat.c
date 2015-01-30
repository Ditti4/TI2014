#include <stdio.h>
#include <stdlib.h>

int str_len(char *string) {
    int i;
    for(i = 0; string[i] != '\0'; i++);
    return i;
}

char *concat(char *string1, char *string2) {
    if(!string1 || !string2)
        return NULL;
    char *concatedstring;
    int len1 = str_len(string1), len2 = str_len(string2);
    if(!(concatedstring = malloc((len1 + len2 + 2) * sizeof(char))))
        return NULL;
    int i;
    for(i = 0; i < len1; i++)
        concatedstring[i] = string1[i];
    concatedstring[len1] = ' ';
    for(i = 0; i < len2; i++)
        concatedstring[len1 + i + 1] = string2[i];
    concatedstring[len1 + len2 + 1] = '\0';
    return concatedstring;
}

int main(int argc, char **argv) {
    char *concated = concat("test", "test2");
    printf(concated);
    putchar('\n');
    return 0;
}
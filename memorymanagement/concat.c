#include <stdio.h>
#include <stdlib.h>
#include "../result.h"

int str_len(char *string) {
    int i;
    for(i = 0; string[i] != '\0'; i++);
    return i;
}

result *concat(char *string1, char *string2) {
    PREPARE_RESULT()
    if(!string1 || !string2)
        return setError(1, initResult());
    char *concatedstring;
    int len1 = str_len(string1), len2 = str_len(string2);
    if(!(concatedstring = malloc((len1 + len2 + 2) * sizeof(char))))
        return setError(1, initResult());
    int i;
    for(i = 0; i < len1; i++)
        concatedstring[i] = string1[i];
    concatedstring[len1] = ' ';
    for(i = 0; i < len2; i++)
        concatedstring[len1 + i + 1] = string2[i];
    concatedstring[len1 + len2 + 1] = '\0';
    return setResult(concatedstring, initResult());    
}

int main(int argc, char **argv) {
    result *rp  = concat("test", "test2");
    if(!rp->errid) {
        printf(rp->result);
        putchar('\n');
    } else {
        printf("Error: %d", rp->errid);
        destroyResult(rp);
    }
    return 0;
}
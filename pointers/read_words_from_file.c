#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACELIKE(A)    A <= 44 || \
                        A == 46 || \
                        A == 47 || \
                        (A >= 58 && A <= 64) || \
                        (A >= 91 && A <= 94) || \
                        A == 96 || \
                        (A >= 123 && A <= 126)

enum ERRORCODES {
    ERROR_NONE = 0,
    ERROR_MALLOC = -1,
    ERROR_REALLOC = -2,
    ERROR_EMPTY_STRING = -3,
    ERROR_EMPTY_ARRAY = -4,
    ERROR_EXISTS = -5,
    ERROR_NO_POS_FOUND = -6,
};

struct wordarray_t {
    int size;
    char **ppwords;
};

int findPositionForName(char *pword, char **ppwords, int start, int size) {
    if(!ppwords) {
        return 0;
    }
    if(strcmp(pword, ppwords[start]) < 0) {
        return start;
    }
    if(strcmp(pword, ppwords[size - 1]) > 0) {
        return size;
    }
    if(strcmp(pword, ppwords[start]) == 0) {
        return ERROR_EXISTS;
    }
    if(strcmp(pword, ppwords[size - 1]) == 0) {
        return ERROR_EXISTS;
    }
    if((size - start) <= 1) {
        return ERROR_NO_POS_FOUND;
    }
    int first_try, second_try;
    int half = ((start + size + ((start + size) % 2)) / 2);
    if(half - 1 > 0 && strcmp(pword, ppwords[half - 1]) == 0) {
        return ERROR_EXISTS;
    }
    if(half + 1 < size && strcmp(pword, ppwords[half + 1]) == 0) {
        return ERROR_EXISTS;
    }
    if(strcmp(pword, ppwords[half - 1]) < 0) {
        first_try = findPositionForName(pword, ppwords, start, half);
        if(first_try != -1) {
            return first_try;
        }
    } else {
        second_try = findPositionForName(pword, ppwords, half, size);
        if(second_try != -1) {
            return second_try;
        }
    }
    return -1;
//     int i;
//     for(i = start; i < size; i++) {
//         if(strcmp(pword, ppwords[i]) < 0) {
//             return i;
//         } else if (strcmp(pword, ppwords[i]) == 0) {
//             return ERROR_EXISTS;
//         }
//     }
}

int rightShiftArray(char ***ppwords, int freepos, int size) {
    if(!(*ppwords = realloc(*ppwords, (size + 1) * sizeof(char*)))) {
        return ERROR_REALLOC;
    }
    int i, j;
    for(i = size; i > freepos; i--) {
        (*ppwords)[i] = (*ppwords)[i - 1];
//         printf("i: %d\n", i);
//         for(j = 0; j <= size; j++) {
//             printf("-> ppwords[%d] = %s\n", j, (*ppwords)[j]);
//         }
//         putchar('\n');
    }
//     printf("loop end\n");
    return 0;
}

struct wordarray_t *fileToArray(FILE *fp, char **ppwords, int ppwordssize) {
    if(!fp) {
        return NULL;
    }
    char *pword = NULL;
    int pwordsize = 0;
    char currentchar;
    int pos;
    while(currentchar = fgetc(fp)) {
        if(currentchar == EOF) {
            break;
        }
        if(SPACELIKE(currentchar)) {
            if(pwordsize) {
                pword = realloc(pword, (pwordsize + 1) * sizeof(char));
                pword[pwordsize] = '\0';
                pos = findPositionForName(pword, ppwords, 0, ppwordssize);
//                 printf("just the pos: %d\n", pos);
//                 printf("word '%s' at pos %d\n", pword, pos);
                if(pos == ERROR_EXISTS || pos == ERROR_NO_POS_FOUND) {
                    pwordsize = 0;
                    free(pword);
                    pword = NULL;
                    continue;
                }
                rightShiftArray(&ppwords, pos, ppwordssize);
                ppwords[pos] = malloc((pwordsize + 1) * sizeof(char));
//                 ppwords = realloc(ppwords, ++ppwordssize * sizeof(char*));
//                 ppwords[ppwordssize - 1] = malloc((pwordsize + 1) * sizeof(char));
                strcpy(ppwords[pos], pword);
//                 strcpy(ppwords[ppwordssize - 1], pword);
//                 ppwords[ppwordssize - 1][pwordsize] = '\0';
//                 putchar('\n');
                ppwordssize++;
//                 printf("pwordsize: %d\n", pwordsize);
                pwordsize = 0;
                free(pword);
                pword = NULL;
//                 printf("after free()\n");
            }
        } else {
            pword = realloc(pword, ++pwordsize * sizeof(char));
            pword[pwordsize - 1] = currentchar;
//             putchar(currentchar);
        }
    }
    
    struct wordarray_t *returnarray = malloc(sizeof(struct wordarray_t));
    returnarray->size = ppwordssize;
    returnarray->ppwords = ppwords;
    return returnarray;
}

int main(int argc, char **argv) {
    if(argc <= 1) {
        printf("usage: %s <list of files>\n", argv[0]);
        return 1;
    }
    
    FILE *fp;
    char **ppwords = NULL;
    int size = 0, i;
    struct wordarray_t *result;
    for(i = 1; i < argc; i++) {
        if(!(fp = fopen(argv[i], "r"))) {
            printf("Couldn't open file %s\n", argv[1]);
            continue;
        }
        result = fileToArray(fp, ppwords, size);
        fclose(fp);
        if(!result->ppwords) {
            printf("Error processing file %s\n", argv[1]);
            continue;
        }
        ppwords = result->ppwords;
        size = result->size;
    }
    
    for(i = 0; i < result->size; i++) {
        printf("ppwords[%d] = %s\n", i, result->ppwords[i]);
    }
    
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SPACELIKE(A)    (A <= 44 && A >= 0) || \
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
    int half = ((start + size + ((start + size) % 2)) / 2);
    if((size - start) <= 1 || half <= 1) {
        return ERROR_NO_POS_FOUND;
    }
    int first_try, second_try;
    if(strcmp(pword, ppwords[half - 1]) == 0) {
        return ERROR_EXISTS;
    }
    if(strcmp(pword, ppwords[half]) == 0) {
        return ERROR_EXISTS;
    }
    if(strcmp(pword, ppwords[half - 1]) < 0) {
        first_try = findPositionForName(pword, ppwords, start, half);
        return first_try;
    } else {
        second_try = findPositionForName(pword, ppwords, half, size);
        return second_try;
    }
}

int rightShiftCharArray(char ***ppwords, int freepos, int size) {
    if(!(*ppwords = realloc(*ppwords, (size + 1) * sizeof(char*)))) {
        return ERROR_REALLOC;
    }
    int i;
    for(i = size; i > freepos; i--) {
        (*ppwords)[i] = (*ppwords)[i - 1];
    }
    return ERROR_NONE;
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
                if(pos == ERROR_EXISTS || pos == ERROR_NO_POS_FOUND) {
//                     printf("Error encountered for word %s (pos %d)\n", pword, pos);
                    pwordsize = 0;
                    free(pword);
                    pword = NULL;
                    continue;
                }
                if(rightShiftCharArray(&ppwords, pos, ppwordssize) != ERROR_NONE) {
                    pwordsize = 0;
                    free(pword);
                    pword = NULL;
                    break;
                }
                ppwords[pos] = malloc((pwordsize + 1) * sizeof(char));
                strcpy(ppwords[pos], pword);
                ppwordssize++;
                pwordsize = 0;
                free(pword);
                pword = NULL;
            }
        } else {
            pword = realloc(pword, ++pwordsize * sizeof(char));
            pword[pwordsize - 1] = currentchar;
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
            printf("Couldn't open file \"%s\". Does it exist and do you have read permission?\n", argv[i]);
            continue;
        }
        result = fileToArray(fp, ppwords, size);
        fclose(fp);
        if(!result->ppwords) {
            printf("Error processing file \"%s\". Is it empty?\n", argv[i]);
            continue;
        }
        ppwords = result->ppwords;
        size = result->size;
        printf("Successfully processed file \"%s\" (%d elements).\n", argv[i], size);
    }
    
//     for(i = 0; i < result->size; i++) {
//         printf("ppwords[%d] = %s\n", i, result->ppwords[i]);
//     }
    
    return 0;
}

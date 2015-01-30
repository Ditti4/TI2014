#include <stdio.h>
#include <stdlib.h>

#include "../result.h"
#include "../errors.h"

int str_len(const char *message) {
    int i;
    for(i = 0; message[i] != '\0'; i++);
    return i;
}

result *toLower(const char *message) {
    if(!message)
        RETURN_ERROR(ERROR_NULL_POINTER);
    int len = str_len(message);
    if(!len)
        RETURN_ERROR(ERROR_EMPTY_STRING);
    char *lower;
    if(!(lower = malloc(len + 1 * sizeof(char))))
        RETURN_ERROR(ERROR_MEM_MALLOC);
    int i;
    for(i = 0; i < len; i++) {
        if(message[i] >= 65 && message[i] <= 91)
            lower[i] = message[i] + 32;
        else
            lower[i] = message[i];
    }
    lower[len] = '\0';
    RETURN_RESULT(lower);
}

void except(int errorid) {
    switch(errorid) {
        case ERROR_NULL_POINTER:
            printf("ERROR_NULL_POINTER");
            break;
        case ERROR_EMPTY_STRING:
            printf("ERROR_EMPTY_STRING");
            break;
        case ERROR_MEM_MALLOC:
            printf("ERROR_MEM_MALLOC");
            break;
    }
    putchar('\n');
}

result *reverseString(const char *message) {
    if(!message)
        RETURN_ERROR(ERROR_NULL_POINTER);
    int len = str_len(message);
    if(!len)
        RETURN_ERROR(ERROR_EMPTY_STRING);
    char *reversed;
    if(!(reversed = malloc(len + 1 * sizeof(char))))
        RETURN_ERROR(ERROR_MEM_MALLOC);
    int i;
    for(i = len - 1; i >= 0; i--) {
        reversed[len - i - 1] = message[i];
    }
    reversed[len] = '\0';
    RETURN_RESULT(reversed);
}

int main(int argc, char **argv) {
    result *reversed, *lower;
    lower = toLower(argv[1]);
    if(!lower->errorid) {
        reversed = reverseString(lower->result);
        if(!reversed->errorid) {
            if(!strcmp(lower->result, reversed->result)) {
                printf("%s ist ein Palindrom.\n", argv[1]);
            } else {
                printf("%s ist kein Palindrom.\n", argv[1]);
            }
        } else {
            except(reversed->errorid);
        }
    } else {
        except(lower->errorid);
    }
    destroyResult(reversed);
    destroyResult(lower);
}
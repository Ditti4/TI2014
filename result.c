#include <stdlib.h>
#include "result.h"

result *init_result() {
    result *resultpointer;
    resultpointer = malloc(sizeof(result));
    return resultpointer;
}

result *set_error(int errid, result *resultpointer) {
    resultpointer->errid = errid;
    return resultpointer;
}

result *set_result(void *inputresult, result *resultpointer) {
    resultpointer->result = inputresult;
    return resultpointer;
}

void destroy_result(result *resultpointer) {
    if(resultpointer->result)
        free(resultpointer->result);
    free(resultpointer);
}
#include <stdlib.h>
#include "result.h"

result *initResult() {
    result *resultpointer;
    resultpointer = malloc(sizeof(result));
    return resultpointer;
}

result *setError(int errorid, result *resultpointer) {
    resultpointer->errorid = errorid;
    return resultpointer;
}

result *setResult(void *inputresult, result *resultpointer) {
    resultpointer->result = inputresult;
    return resultpointer;
}

void destroyResult(result *resultpointer) {
    if(resultpointer->result)
        free(resultpointer->result);
    free(resultpointer);
}
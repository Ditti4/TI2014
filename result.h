#ifndef RD_RESULT_H
#define RD_RESULT_H

#define RETURN_RESULT(RES)  RETURN(RES, 0)
#define RETURN_ERROR(ID)    RETURN(NULL, ID)
#define RETURN(RES, ID)     return setResult(RES, setError(ID, initResult()))
                            
typedef struct functionresult {
    void *result;
    int errorid;
} result;

result *initResult();
result *setError(int, result *);
result *setResult(void *, result *);
void destroyResult(result *);

#endif
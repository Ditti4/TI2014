#ifndef RD_RESULT_H
#define RD_RESULT_H

#define PREPARE_RESULT()    result *resultpointer;\
                            resultpointer = malloc(sizeof(result));\
                            resultpointer->errid = 0;
#define SET_ERRID(ID)       resultpointer->errid = ID;
#define RETURN_RESULT(RES)  { resultpointer->result = RES;\
                            return resultpointer; }
#define RETURN_ERROR(ID)    { resultpointer->result = NULL;\
                            resultpointer->errid = ID;\
                            return resultpointer; }

typedef struct functionresult {
    void *result;
    int errid;
} result;

result *initResult();
result *setError(int, result *);
result *setResult(void *, result *);
void destroyResult(result *);

#endif
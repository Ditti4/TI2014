#ifndef RD_RESULT_H
#define RD_RESULT_H

#define RETURN_RESULT(RES)  RETURN(RES, 0)
#define RETURN_ERROR(ID)    RETURN(NULL, ID)
#define RETURN(RES, ID)     return set_result(RES, set_error(ID, init_result()))
                            
typedef struct functionresult {
    void *result;
    int errid;
} result;

result *init_result();
result *set_error(int, result *);
result *set_result(void *, result *);
void destroy_result(result *);

#endif
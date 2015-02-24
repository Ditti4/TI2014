#ifndef RD_ERRORS_H
#define RD_ERRORS_H

enum ERROR {
    ERROR_NONE = 0,
    ERROR_MEM_MALLOC = -64,
    ERROR_MEM_REALLOC,
    ERROR_NULL_POINTER,
    ERROR_EMPTY_STRING,
    ERROR_FILE_OPEN,
    ERROR_FILE_READ,
    ERROR_FILE_WRITE,
};

#endif
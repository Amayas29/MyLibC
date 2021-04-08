#ifndef LIB_ERROR_H_
#define LIB_ERROR_H_

#include <stdio.h>

typedef enum {
    NullPointerError,
    AllocationError,
    IndexOutOfBoundsError,
} error_t;

const char *ERROR_MESSAGES[] = {
    "NullPointerError : The pointer is NULL",
    "AllocationError : an allocation error has occurred",
    "IndexOutOfBoundsError : acces to an out of bounds index"};

void raise(error_t err, const char *FILE, const char *FUNCTION, const int LINE, char *details);

#endif
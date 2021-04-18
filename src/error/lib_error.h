#ifndef LIB_ERROR_H_
#define LIB_ERROR_H_

#include <stdio.h>

typedef enum {
    NullPointerError,
    AllocationError,
    IndexOutOfBoundsError,
    ValueError,
} error_t;

void raise_error(error_t err, const char *FILE, const char *FUNCTION, const int LINE, char *details);

#endif
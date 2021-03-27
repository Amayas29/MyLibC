#ifndef _ERROR_H
#define _ERROR_H

#include <stdio.h>

typedef enum {
    TMP
} error_t;

const char *ERROR_MESSAGES[] = {};

void raise(error_t err, const char *FILE, const char *FUNCTION, const int LINE, char *details);

#endif
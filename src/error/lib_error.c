#include "lib_error.h"

#include <stdio.h>

void raise(error_t err, const char *FILE, const char *FUNCTION, const int LINE, char *details) {
    fprintf(stderr, "%s in %s -- %s at %d.\n", ERROR_MESSAGES[err], FILE, FUNCTION, LINE);
    if (details)
        fprintf(stderr, "\t >> Details: %s\n", details);
}
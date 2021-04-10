#include "lib_error.h"

#include <stdio.h>

static const char *ERROR_MESSAGES[] = {
    "NullPointerError : a pointer is NULL",
    "AllocationError : an allocation error has occurred",
    "IndexOutOfBoundsError : access to an out of bounds index"};

void raise_error(error_t err, const char *FILE, const char *FUNCTION, const int LINE, char *details) {
    fprintf(stderr, "%s in %s -- %s at ligne %d.\n", ERROR_MESSAGES[err], FILE, FUNCTION, LINE);
    if (details)
        fprintf(stderr, "\t >> Details: %s\n", details);
}

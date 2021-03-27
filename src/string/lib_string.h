#ifndef _LIB_STRING_H
#define _LIB_STRING_H

/* Split a string according to the delimiter */
char **split_l(const char str[], const char delim[], int *length); // Using linked list
char **split_r(const char str[], const char delim[], int *length); // Using realloc

#endif

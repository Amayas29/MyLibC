#ifndef __LIB_STRING_H__
#define __LIB_STRING_H__

/* Split a string according to the delimiter */
char **split_l(const char str[], const char delim[], int *length); // Using linked list
char **split_r(const char str[], const char delim[], int *length); // Using realloc

#endif

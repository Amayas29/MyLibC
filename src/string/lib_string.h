#ifndef LIB_STRING_H_
#define LIB_STRING_H_

/* Split a string according to the delimiter */
char **split_l(const char str[], const char delim[], int *length); // Using linked list
char **split_r(const char str[], const char delim[], int *length); // Using realloc

#endif

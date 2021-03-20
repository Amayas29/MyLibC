#ifndef __LIB_STRING_H__
#define __LIB_STRING_H__

/*
* Version 01: using linked list
* Version 02: with realloc
*/

/* Split a string according to the delimiter */
char **split_l(const char str[], const char delim[], int *length); // Using linked list
char **split_r(const char str[], const char delim[], int *length); // Using realloc

#endif
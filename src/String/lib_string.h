#ifndef __LIB_STRING_H__
#define __LIB_STRING_H__

/*
* Version 01: without using realloc
* Version 02: with realloc (in progress)
*/

/* Split a string according to the delimiter */
char **split(const char str[],const char delim[], int *length);

#endif
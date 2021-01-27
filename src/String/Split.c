#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
* Version 01: without using realloc
* Version 02: with realloc (in progress)
*/

/* Split a string according to the delimiter */
char **split(const char str[],const char delim[], int *length) {

    if(!str || !delim) return NULL;

    char *_str = strdup(str);
    if(!str) return NULL;

    struct elt {
        char *str;
        struct elt *next;
    };

    struct elt *head = NULL;
    struct elt *tmp = NULL;
    struct elt *end = NULL;
    *length = 0;

    char *sep = strtok(_str, delim);
    while(sep) {

        tmp = malloc(sizeof(struct elt));
        if(!tmp) continue;

        if(!head)
            head = tmp;
        else
            end->next = tmp;
    
        tmp->str = strdup(sep);
        tmp->next = NULL;
        end = tmp;

        (*length) ++;
        sep = strtok(NULL, delim);
    }

    free(_str);

    char ** tab = NULL;
    if(*length != 0)
        tab = malloc(sizeof(char *) * *length);

    for(int i = 0; head; i++) {
        if(tab)
            tab[ i ] = head->str;
        tmp = head->next;
        free(head);
        head = tmp;
    }

    return tab;   
}

int main() {

    int len = 0;
   
    char **tab = split("split_string_by_delimiter_test", "_" ,&len);

    for(int i = 0; i < len; i++) {
        printf("%s\n", tab[i]);
        free(tab[i]);
    }

    free(tab);

    return 0;
}

#include "lib_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_l(const char str[], const char delim[], int *length) {
    if (!str || !delim) return NULL;

    char *_str = strdup(str);
    if (!_str) return NULL;

    struct elt {
        char *str;
        struct elt *next;
    };

    struct elt *head = NULL;
    struct elt *tmp = NULL;
    struct elt *end = NULL;
    *length = 0;

    char *sep = strtok(_str, delim);
    while (sep) {
        tmp = malloc(sizeof(struct elt));
        if (!tmp) continue;

        if (!head)
            head = tmp;
        else
            end->next = tmp;

        tmp->str = strdup(sep);
        tmp->next = NULL;
        end = tmp;

        (*length)++;
        sep = strtok(NULL, delim);
    }

    free(_str);

    char **tab = NULL;
    if (*length != 0)
        tab = malloc(sizeof(char *) * *length);

    for (int i = 0; head; i++) {
        if (tab)
            tab[i] = head->str;
        tmp = head->next;
        free(head);
        head = tmp;
    }

    return tab;
}

char **split_r(const char str[], const char delim[], int *length) {
    if (!str || !delim) return NULL;

    char *_str = strdup(str);
    if (!_str) {
        fprintf(stderr, "Allocation error\n");
        return NULL;
    }

    *length = 0;

    const int INCREMENT = 10;
    int max_lenght = INCREMENT;

    char **tab = malloc(sizeof(char *) * max_lenght);
    if (!tab) {
        fprintf(stderr, "Allocation error\n");
        free(_str);
        return NULL;
    }

    char *sep = strtok(_str, delim);

    while (sep) {
        if (*length == max_lenght) {
            max_lenght += INCREMENT;
            tab = realloc(tab, max_lenght * sizeof(char *));
        }

        tab[*length] = strdup(sep);

        if (!tab[*length]) {
            fprintf(stderr, "Allocation error\n");
            for (int j = 0; j < *length; j++)
                free((tab[j]));
            free(tab);
            free(_str);
            *length = 0;
            return NULL;
        }

        (*length)++;
        sep = strtok(NULL, delim);
    }

    free(_str);
    tab = realloc(tab, *length * sizeof(char *));

    return tab;
}

int main() {
    int len = 0;

    char **tab = split_r("split_string_by_delimiter_test", "_", &len);

    for (int i = 0; i < len; i++) {
        printf("%s\n", tab[i]);
        free(tab[i]);
    }

    free(tab);

    return 0;
}

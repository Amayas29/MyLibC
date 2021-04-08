#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

ArrayList *ar_create();
void ar_add(ArrayList *arraylist, void *element);
void ar_add_index(ArrayList *arraylist, int index, void *element);
void ar_clear(ArrayList *arraylist);
ArrayList *ar_clone(ArrayList *arraylist);
int ar_contains(ArrayList *arraylist, void *element);
void *ar_get(ArrayList *arraylist, int index);
int ar_index_of(ArrayList *arraylist, void *element);
void *ar_remove_index(ArrayList *arraylist, int index);
int ar_remove(ArrayList *arraylist, void *element);
void *ar_set(ArrayList *arraylist, int index, void *element);
ArrayList *ar_filter(ArrayList *arraylist, int (*property)(void *data));
void *ar_map(ArrayList *arraylist, void (*map_fct)(void *data));
ArrayList *ar_quicksort(ArrayList *arraylist, int (*compare)(void *data_1, void *data_2));
void ar_free(ArrayList *arraylist);

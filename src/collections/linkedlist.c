#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

LinkedList *create();
void add(LinkedList *linkedList, void *element);
void add_index(LinkedList *linkedList, int index, void *element);
void clear(LinkedList *linkedList);
LinkedList *clone(LinkedList *linkedList);
int contains(LinkedList *linkedList, void *element);
void *get(LinkedList *linkedList, int index);
int index_of(LinkedList *linkedList, void *element);
void *remove_index(LinkedList *linkedList, int index);
int remove(LinkedList *linkedList, void *element);
void *remove_index(LinkedList *linkedlist, int index);
void *set(LinkedList *linkedList, int index, void *element);
LinkedList *sub_list(LinkedList *linkedList, int start, int end);
LinkedList *filter(LinkedList *linkedList, int (*property)(void *data));
void *map(LinkedList *linkedList, void (*map_fct)(void *data));
LinkedList *quicksort(LinkedList *linkedList, int (*compare)(void *data_1, void *data_2));
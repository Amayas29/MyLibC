#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

#include "lib_error.h"

LinkedList *create() {
    LinkedList *linkedlist = malloc(sizeof(LinkedList));
    if (!linkedlist) {
        raise(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    linkedlist->_last = NULL;
    linkedlist->elements = NULL;
    linkedlist->size = 0;
    return linkedlist;
}

void add(LinkedList *linkedlist, void *data) {
    if (!linkedlist) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    if (!data) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return;
    }

    Element *element = malloc(sizeof(Element));

    if (!element) {
        raise(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return;
    }

    element->data = data;
    element->next = NULL;

    if (linkedlist->_last) {
        linkedlist->_last->next = element;
        linkedlist->_last = element;
        return;
    }

    linkedlist->_last = element;
    linkedlist->elements = element;
}

void add_index(LinkedList *linkedlist, int index, void *data);
void clear(LinkedList *linkedlist);
LinkedList *clone(LinkedList *linkedlist);
int contains(LinkedList *linkedlist, void *data);
void *get(LinkedList *linkedlist, int index);
int index_of(LinkedList *linkedlist, void *data);
void *remove_index(LinkedList *linkedlist, int index);
int remove(LinkedList *linkedlist, void *data);
void *remove_index(LinkedList *linkedlist, int index);
void *set(LinkedList *linkedlist, int index, void *data);
LinkedList *sub_list(LinkedList *linkedlist, int start, int end);
LinkedList *filter(LinkedList *linkedlist, int (*property)(void *data));
void *map(LinkedList *linkedlist, void (*map_fct)(void *data));
LinkedList *quicksort(LinkedList *linkedlist, int (*compare)(void *data_1, void *data_2));
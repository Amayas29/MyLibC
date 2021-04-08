#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

typedef struct element {
    void *data;
    struct element *next;
} Element;

typedef struct linkedlist {
    Element *_last;
    Element *elements;
    int size;
} LinkedList;

LinkedList *create();
void add(LinkedList *linkedlist, void *data);
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

#endif

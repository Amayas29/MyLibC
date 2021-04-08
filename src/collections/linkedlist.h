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
    void (*free_data)(void *data);
    void *(*copy_data)(void *data);
    void (*print_data)(void *data);
} LinkedList;

LinkedList *lk_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data));
void lk_add(LinkedList *linkedlist, void *data);
void lk_add_index(LinkedList *linkedlist, int index, void *data);
void lk_clear(LinkedList *linkedlist);
LinkedList *lk_clone(LinkedList *linkedlist);
int lk_contains(LinkedList *linkedlist, void *data);
void *lk_get(LinkedList *linkedlist, int index);
int lk_index_of(LinkedList *linkedlist, void *data);
int lk_remove(LinkedList *linkedlist, void *data);
void *lk_remove_index(LinkedList *linkedlist, int index);
void *lk_set(LinkedList *linkedlist, int index, void *data);
LinkedList *lk_sub(LinkedList *linkedlist, int start, int end);
LinkedList *lk_filter(LinkedList *linkedlist, int (*property)(void *data));
void *lk_map(LinkedList *linkedlist, void (*map_fct)(void *data));
LinkedList *lk_quicksort(LinkedList *linkedlist, int (*compare)(void *data_1, void *data_2));
void lk_free(LinkedList *linkedlist);

#endif

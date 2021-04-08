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

LinkedList *create_linkedlist(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data));
void add_linkedlist(LinkedList *linkedlist, void *data);
void add_index_linkedlist(LinkedList *linkedlist, int index, void *data);
void clear_linkedlist(LinkedList *linkedlist);
LinkedList *clone_linkedlist(LinkedList *linkedlist);
int contains_linkedlist(LinkedList *linkedlist, void *data);
void *get_linkedlist(LinkedList *linkedlist, int index);
int index_of_linkedlist(LinkedList *linkedlist, void *data);
int remove_linkedlist(LinkedList *linkedlist, void *data);
void *remove_index_linkedlist(LinkedList *linkedlist, int index);
void *set_linkedlist(LinkedList *linkedlist, int index, void *data);
LinkedList *sub_linkedlist(LinkedList *linkedlist, int start, int end);
LinkedList *filter_linkedlist(LinkedList *linkedlist, int (*property)(void *data));
void *map_linkedlist(LinkedList *linkedlist, void (*map_fct)(void *data));
LinkedList *quicksort_linkedlist(LinkedList *linkedlist, int (*compare)(void *data_1, void *data_2));
void free_linkedlist(LinkedList *linkedlist);

#endif

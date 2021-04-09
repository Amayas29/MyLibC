#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#define INCREMENT 100
#define INITIAL_CAPACITY 100

typedef struct element {
    void *data;
} Element;

typedef struct arraylist {
    Element *array;
    int size;
    int capacity;
    void (*free_data)(void *data);
    void *(*copy_data)(void *data);
    void (*print_data)(void *data);
    int (*compare_data)(void *data_1, void *data_2);
} ArrayList;

ArrayList *ar_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data), int (*compare_data)(void *data_1, void *data_2));
int ar_add(ArrayList *arraylist, void *data);
int ar_add_index(ArrayList *arraylist, int index, void *data);
void ar_clear(ArrayList *arraylist);
ArrayList *ar_clone(ArrayList *arraylist);
int ar_contains(ArrayList *arraylist, void *data);
void *ar_get(ArrayList *arraylist, int index);
int ar_index_of(ArrayList *arraylist, void *data);
void *ar_remove_index(ArrayList *arraylist, int index);
int ar_remove(ArrayList *arraylist, void *data);
void *ar_set(ArrayList *arraylist, int index, void *data);
ArrayList *ar_filter(ArrayList *arraylist, int (*property)(void *data));
void ar_map(ArrayList *arraylist, void (*map_fct)(void *data));
void ar_quicksort(ArrayList *arraylist, int (*compare)(void *data_1, void *data_2));
void ar_free(ArrayList *arraylist);

#endif
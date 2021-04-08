#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

#define INCREMENT 100
#define INITIAL_CAPACITY 100

typedef struct element {
    void *data;
} Element;

typedef struct arraylist {
    Element **aray;
    int size;
    int capacity;
} ArrayList;

ArrayList *create();
void add(ArrayList *arraylist, void *element);
void add_index(ArrayList *arraylist, int index, void *element);
void clear(ArrayList *arraylist);
ArrayList *clone(ArrayList *arraylist);
int contains(ArrayList *arraylist, void *element);
void *get(ArrayList *arraylist, int index);
int index_of(ArrayList *arraylist, void *element);
void *remove_index(ArrayList *arraylist, int index);
int remove(ArrayList *arraylist, void *element);
void *remove_index(ArrayList *arraylist, int index);
void *set(ArrayList *arraylist, int index, void *element);
ArrayList *filter(ArrayList *arraylist, int (*property)(void *data));
void *map(ArrayList *arraylist, void (*map_fct)(void *data));
ArrayList *quicksort(ArrayList *arraylist, int (*compare)(void *data_1, void *data_2));

#endif
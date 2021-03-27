#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

typedef struct list {
    void *data;
    struct list *next;
} List;

typedef struct arraylist {
    List *list;
    int length;
} ArrayList;

void add(ArrayList *arraylist, void *element);
void add_index(ArrayList *arraylist, int index, void *element);
void clear(ArrayList *arraylist);
ArrayList *clone(ArrayList *arraylist);
int contains(ArrayList *arraylist, void *element);
void *get(ArrayList *arraylist, int index);
void *remove_index(ArrayList *arraylist, int index);
int remove(ArrayList *arraylist, void *element);
void *set(ArrayList *arraylist, int index, void *element);

#endif

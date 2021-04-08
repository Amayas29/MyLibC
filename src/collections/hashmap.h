#ifndef HASH_MAP_H_
#define HASH_MAP_H_

typedef struct element {
    void *key;
    void *value;
    struct element *next;
} Element;

typedef struct hashmap {
    int size;
    int capacity;
    Element **harray;
    int (*hash)(void *data);
} HashMap;

HashMap *create(int capacity, int (*hash)(void *data));
void clear(HashMap *hashmap);
HashMap *clone(HashMap *hashmap);
int contains_key(HashMap *hashmap, void *key);
int contains_value(HashMap *hashmap, void *value);
void *get(HashMap *hashmap, void *key);
void *put(HashMap *hashmap, void *key, void *value);
void remove(HashMap *hashmap, void *key);

#endif
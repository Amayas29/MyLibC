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
    double (*key_function)(void *data);
    void (*free_key)(void *key);
    void (*free_data)(void *data);
    void *(*clone_data)(void *data);
    void *(*clone_key)(void *key);
    int (*compare_key)(void *key_1, void *key_2);
    int (*compare_data)(void *data_1, void *data_2);
} HashMap;

HashMap *hm_create(int capacity, double (*key_function)(void *data), void (*free_key)(void *key), void (*free_data)(void *data), void *(*clone_key)(void *key), void *(*clone_data)(void *data), int (*compare_key)(void *key_1, void *key_2), int (*compare_data)(void *data_1, void *data_2));
void hm_clear(HashMap *hashmap);
HashMap *hm_clone(HashMap *hashmap);
int hm_contains_key(HashMap *hashmap, void *key);
int hm_contains_value(HashMap *hashmap, void *value);
void *hm_get(HashMap *hashmap, void *key);
void *hm_put(HashMap *hashmap, void *key, void *value);
void hm_remove(HashMap *hashmap, void *key);
void hm_free(HashMap *hashmap);

#endif
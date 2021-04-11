#include "hashmap.h"

#include <stdio.h>
#include <stdlib.h>

HashMap *hm_create(int capacity, int (*hash)(void *data));
void hm_clear(HashMap *hashmap);
HashMap *hm_clone(HashMap *hashmap);
int hm_contains_key(HashMap *hashmap, void *key);
int hm_contains_value(HashMap *hashmap, void *value);
void *hm_get(HashMap *hashmap, void *key);
void *hm_put(HashMap *hashmap, void *key, void *value);
void hm_remove(HashMap *hashmap, void *key);
void hm_free(HashMap *hashmap);
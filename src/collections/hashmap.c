#include "hashmap.h"

#include <stdio.h>
#include <stdlib.h>

HashMap *create(int capacity, int (*hash)(void *data));
void clear(HashMap *hashmap);
HashMap *clone(HashMap *hashmap);
int contains_key(HashMap *hashmap, void *key);
int contains_value(HashMap *hashmap, void *value);
void *get(HashMap *hashmap, void *key);
void *put(HashMap *hashmap, void *key, void *value);
void remove(HashMap *hashmap, void *key);
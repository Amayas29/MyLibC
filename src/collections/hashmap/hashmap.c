#include "hashmap.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../error/lib_error.h"

static int hash_function(double key, int length);

HashMap *hm_create(int capacity, double (*key_function)(void *data), void (*free_key)(void *key), void (*free_data)(void *data),
                   void *(*clone_key)(void *key), void *(*clone_data)(void *data),
                   int (*compare_key)(void *key_1, void *key_2), int (*compare_data)(void *data_1, void *data_2)) {
    if (!key_function) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The key function does not exist");
        return NULL;
    }

    if (!free_data || !free_key || !clone_key || !clone_data || !compare_key || !compare_data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "Functions of data-key does not exist");
        return NULL;
    }

    if (capacity < 0) {
        raise_error(ValueError, __FILE__, __FUNCTION__, __LINE__, "The capacity must be greater than zero");
        return NULL;
    }

    HashMap *hashmap = malloc(sizeof(HashMap));

    if (!hashmap) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    hashmap->harray = malloc(sizeof(Element *) * capacity);

    if (!hashmap->harray) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        free(hashmap);
        return NULL;
    }

    for (int i = 0; i < capacity; i++)
        hashmap->harray[i] = NULL;

    hashmap->capacity = capacity;
    hashmap->size = 0;
    hashmap->key_function = key_function;

    hashmap->free_data = free_data;
    hashmap->free_key = free_key;
    hashmap->clone_data = clone_data;
    hashmap->clone_key = clone_key;

    hashmap->compare_key = compare_key;
    hashmap->compare_data = compare_data;

    return hashmap;
}

void hm_clear(HashMap *hashmap) {
    if (!hashmap) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The hashmap does not exist");
        return;
    }

    for (int i = 0; i < hashmap->capacity; i++) {
        Element *tmp = hashmap->harray[i];

        while (hashmap->harray[i]) {
            hashmap->free_data(hashmap->harray[i]->value);
            hashmap->free_key(hashmap->harray[i]->key);

            tmp = hashmap->harray[i]->next;
            free(hashmap->harray[i]);
            hashmap->harray[i] = tmp;
        }
    }

    hashmap->size = 0;
}

HashMap *hm_clone(HashMap *hashmap) {
    if (!hashmap) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The hashmap does not exist");
        return NULL;
    }

    HashMap *cloned = hm_create(hashmap->capacity, hashmap->key_function, hashmap->free_key, hashmap->free_data,
                                hashmap->clone_key, hashmap->clone_data, hashmap->compare_key,
                                hashmap->compare_data);

    if (!cloned) return NULL;

    for (int i = 0; i < hashmap->capacity; i++) {
        Element *tail = NULL;
        Element *other = hashmap->harray[i];
        while (other) {
            Element *new_node = malloc(sizeof(Element));
            if (!new_node) {
                raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
                hm_free(cloned);
                return NULL;
            }

            new_node->key = hashmap->clone_key(other->key);
            new_node->value = hashmap->clone_data(other->value);
            new_node->next = NULL;

            other = other->next;

            if (!tail) {
                cloned->harray[i] = new_node;
                tail = new_node;
                continue;
            }

            tail->next = new_node;
            tail = new_node;
        }
    }
}

int hm_contains_key(HashMap *hashmap, void *key) {
    if (!hashmap) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The hashmap does not exist");
        return 0;
    }

    if (!key) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The key does not exist");
        return 0;
    }

    int index = hash_function(hashmap->key_function(key), hashmap->capacity);

    for (Element *curr = hashmap->harray[index]; curr; curr = curr->next)
        if (hashmap->compare_key(curr->key, key) == 0) return 1;

    return 0;
}

int hm_contains_value(HashMap *hashmap, void *value) {
    if (!hashmap) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The hashmap does not exist");
        return 0;
    }

    if (!value) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The value does not exist");
        return 0;
    }

    for (int i = 0; i < hashmap->capacity; i++)
        for (Element *curr = hashmap->harray[i]; curr; curr = curr->next)
            if (hashmap->compare_data(curr->value, value) == 0) return 1;

    return 0;
}

void *hm_get(HashMap *hashmap, void *key) {
    if (!hashmap) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The hashmap does not exist");
        return NULL;
    }

    if (!key) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The key does not exist");
        return NULL;
    }

    int index = hash_function(hashmap->key_function(key), hashmap->capacity);

    for (Element *curr = hashmap->harray[index]; curr; curr = curr->next)
        if (hashmap->compare_key(curr->key, key) == 0) return curr->value;

    return NULL;
}

void *hm_put(HashMap *hashmap, void *key, void *value) {
    if (!hashmap) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The hashmap does not exist");
        return NULL;
    }

    if (!key) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The key does not exist");
        return NULL;
    }

    if (!value) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The value does not exist");
        return NULL;
    }

    int index = hash_function(hashmap->key_function(key), hashmap->capacity);

    Element *curr = NULL;
    for (curr = hashmap->harray[index]; curr && hashmap->compare_key(curr->key, key) != 0; curr = curr->next) continue;

    if (curr) {
        void *old_data = curr->value;
        curr->value = value;
        return old_data;
    }

    Element *new_node = malloc(sizeof(Element));

    if (!new_node) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    new_node->key = key;
    new_node->value = value;

    new_node->next = hashmap->harray[index];
    hashmap->harray[index] = new_node;

    return NULL;
}

void hm_remove(HashMap *hashmap, void *key) {
    if (!hashmap) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The hashmap does not exist");
        return;
    }

    if (!key) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The key does not exist");
        return;
    }

    int index = hash_function(hashmap->key_function(key), hashmap->capacity);

    if (!hashmap->harray[index]) return;
    if (hashmap->compare_key(hashmap->harray[index]->key, key) == 0) {  // On head
        Element *deleted = hashmap->harray[index];
        hashmap->harray[index] = deleted->next;

        hashmap->free_data(deleted->value);
        if (deleted->key != key)
            hashmap->free_key(deleted->key);

        free(deleted);
        return;
    }

    Element *pred = NULL, *curr = hashmap->harray[index];
    for (; curr && hashmap->compare_key(curr->key, key) != 0; pred = curr, curr = curr->next) continue;

    if (!curr) return;

    pred = curr->next;

    hashmap->free_data(curr->value);
    if (curr->key != key)
        hashmap->free_key(curr->key);

    free(curr);
}

void hm_free(HashMap *hashmap) {
    if (!hashmap) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The hashmap does not exist");
        return;
    }

    hm_clear(hashmap);
    free(hashmap->harray);
    free(hashmap);
}

static int hash_function(double key, int lenght) {
    float a = (sqrt(5) - 1) / 2.0;
    double kA = key * a;
    long kA_int = (long)kA;

    return (int)(lenght * (kA - kA_int));
}

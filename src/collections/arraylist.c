#include "arraylist.h"

#include <stdio.h>
#include <stdlib.h>

#include "../error/lib_error.h"

ArrayList *ar_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data), int (*compare_data)(void *data_1, void *data_2)) {
    if (!free_data || !copy_data || !print_data || !compare_data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "Functions of data does not exist");
        return NULL;
    }

    ArrayList *arraylist = malloc(sizeof(ArrayList));
    if (!arraylist) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    arraylist->size = 0;
    arraylist->capacity = INITIAL_CAPACITY;
    arraylist->free_data = free_data;
    arraylist->copy_data = copy_data;
    arraylist->print_data = print_data;
    arraylist->compare_data = compare_data;

    arraylist->array = malloc(sizeof(Element) * arraylist->capacity);
    if (!arraylist->array) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        free(arraylist);
        return NULL;
    }

    for (int i = 0; i < arraylist->capacity; i++)
        arraylist->array[i].data = NULL;

    return arraylist;
}

int ar_add(ArrayList *arraylist, void *data) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The arraylist does not exist");
        return 0;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return 0;
    }

    if (arraylist->size == arraylist->capacity) {
        arraylist->capacity += INCREMENT;

        arraylist->array = realloc(arraylist->array, arraylist->capacity * sizeof(Element));
        if (!arraylist->array) {
            raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
            ar_free(arraylist);
            return 0;
        }

        for (int i = arraylist->size; i < arraylist->capacity; i++)
            arraylist->array[i].data = NULL;
    }

    arraylist->array[arraylist->size++].data = data;
    return 1;
}

int ar_add_index(ArrayList *arraylist, int index, void *data) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return 0;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return 0;
    }

    if (index < 0 || index > arraylist->size) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return 0;
    }

    if (arraylist->size == arraylist->capacity) {
        arraylist->capacity += INCREMENT;

        arraylist->array = realloc(arraylist->array, arraylist->capacity * sizeof(Element));
        if (!arraylist->array) {
            raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
            ar_free(arraylist);
            return 0;
        }

        for (int i = arraylist->size; i < arraylist->capacity; i++)
            arraylist->array[i].data = NULL;
    }

    for (int i = arraylist->size; i > index; i--) {
        void *tmp = arraylist->array[i].data;
        arraylist->array[i].data = arraylist->array[i - 1].data;
        arraylist->array[i - 1].data = tmp;
    }

    arraylist->size++;
    arraylist->array[index].data = data;
    return 1;
}

void ar_clear(ArrayList *arraylist) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    for (int i = 0; i < arraylist->size; i++) {
        arraylist->free_data(arraylist->array[i].data);
        arraylist->array[i].data = NULL;
    }

    arraylist->size = 0;
}

ArrayList *ar_clone(ArrayList *arraylist) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The arraylist does not exist");
        return NULL;
    }

    ArrayList *cloned = ar_create(arraylist->free_data, arraylist->copy_data, arraylist->print_data, arraylist->compare_data);
    if (!cloned) return NULL;

    for (int i = 0; i < arraylist->size; i++)
        if (!ar_add(cloned, arraylist->copy_data(arraylist->array[i].data))) {
            ar_free(cloned);
            return NULL;
        }

    return cloned;
}

int ar_contains(ArrayList *arraylist, void *data) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The arraylist does not exist");
        return 0;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return 0;
    }

    for (int i = 0; i < arraylist->size; i++)
        if (arraylist->compare_data(arraylist->array[i].data, data) == 0) return 1;

    return 0;
}

void *ar_get(ArrayList *arraylist, int index) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    if (index < 0 || index >= arraylist->size) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    return arraylist->array[index].data;
}

int ar_index_of(ArrayList *arraylist, void *data) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The arraylist does not exist");
        return -1;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return -1;
    }

    for (int i = 0; i < arraylist->size; i++)
        if (arraylist->compare_data(arraylist->array[i].data, data) == 0) return i;

    return -1;
}

void *ar_remove_index(ArrayList *arraylist, int index) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    if (index < 0 || index >= arraylist->size) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    void *data = arraylist->array[index].data;
    arraylist->array[index].data = NULL;

    for (int i = index; i < arraylist->size - 1; i++)
        arraylist->array[i].data = arraylist->array[i + 1].data;

    arraylist->size--;
    return data;
}

int ar_remove(ArrayList *arraylist, void *data);

void *ar_set(ArrayList *arraylist, int index, void *data) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return 0;
    }

    if (index < 0 || index >= arraylist->size) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    void *old_data = arraylist->array[index].data;
    arraylist->array[index].data = data;
    return old_data;
}

ArrayList *ar_filter(ArrayList *arraylist, int (*property)(void *data)) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    if (!property) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The filter function does not exist");
        return NULL;
    }

    ArrayList *filtred = ar_create(arraylist->free_data, arraylist->copy_data, arraylist->print_data, arraylist->compare_data);
    if (!filtred) return NULL;

    for (int i = 0; i < arraylist->size; i++)
        if (property(arraylist->array[i].data))
            if (!ar_add(filtred, arraylist->copy_data(arraylist->array[i].data))) {
                ar_free(filtred);
                return NULL;
            }

    return filtred;
}

void ar_map(ArrayList *arraylist, void (*map_fct)(void *data)) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    if (!map_fct) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The map function does not exist");
        return;
    }

    for (int i = 0; i < arraylist->size; i++)
        map_fct(arraylist->array[i].data);
}

void ar_quicksort(ArrayList *arraylist, int (*compare)(void *data_1, void *data_2));

void ar_free(ArrayList *arraylist) {
    if (!arraylist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    ar_clear(arraylist);
    free(arraylist->array);
    free(arraylist);
}

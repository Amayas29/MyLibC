#include "tuple.h"

#include <stdarg.h>
#include <stdio.h>

#include "../error/lib_error.h"

Tuple *tu_create(void (*add_data)(void *one, void *two), void (*sub_data)(void *one, void *two),
                 void (*mult_data)(void *one, void *two), void (*div_data)(void *one, void *two),
                 void *data, ...) {
    if (!add_data || !sub_data || !mult_data || !div_data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The tuple functions does not exist");
        return NULL;
    }

    Tuple *tuple = malloc(sizeof(Tuple));

    if (!tuple) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    tuple->add_data = add_data;
    tuple->div_data = div_data;
    tuple->mult_data = mult_data;
    tuple->sub_data = sub_data;

    tuple->array = NULL;  // TODO

    return tuple;
}

void tu_add_tuple(Tuple *self, Tuple *other) {
}

void tu_sub_tuple(Tuple *self, Tuple *other) {
}

void tu_mult_tuple(Tuple *self, Tuple *other) {
}

void tu_mult(Tuple *self, void *k) {
    if (!self) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The tuple does not exist");
        return;
    }

    for (int i = 0; i < self->array->size; i++)
        self->mult_data(self->array->array[i].data, k);
}

void tu_add(Tuple *self, void *k) {
    if (!self) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The tuple does not exist");
        return;
    }

    for (int i = 0; i < self->array->size; i++)
        self->add_data(self->array->array[i].data, k);
}

void tu_sub(Tuple *self, void *k) {
    if (!self) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The tuple does not exist");
        return;
    }

    for (int i = 0; i < self->array->size; i++)
        self->sub_data(self->array->array[i].data, k);
}

void tu_div(Tuple *self, void *k) {
    if (!self) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The tuple does not exist");
        return;
    }

    for (int i = 0; i < self->array->size; i++)
        self->div_data(self->array->array[i].data, k);
}

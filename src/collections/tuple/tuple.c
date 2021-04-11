#include "tuple.h"

#include <stdarg.h>
#include <stdio.h>

Tuple *tu_create(void (*add_data)(void *one, void *two), void (*sub_data)(void *one, void *two),
                 void (*mult_data)(void *one, void *two), void (*div_data)(void *one, void *two),
                 void *data, ...);

void tu_add_tuple(Tuple *self, Tuple *other);
void tu_sub_tuple(Tuple *self, Tuple *other);
void tu_mult_tuple(Tuple *self, Tuple *other);

void tu_mult(Tuple *self, void *k);
void tu_add(Tuple *self, void *k);
void tu_mult(Tuple *self, void *k);
void tu_div(Tuple *self, void *k);
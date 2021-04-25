#ifndef STACK_H_
#define STACK_H_

#include "../linkedlist/linkedlist.h"

typedef LinkedList Stack;

Stack *st_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data), int (*compare_data)(void *data_1, void *data_2));

int st_push(Stack *stack, void *data);
void *st_pop(Stack *stack);

void st_clear(Stack *stack);

int st_is_empty(Stack *stack);

void *st_get_head(Stack *stack);

#endif
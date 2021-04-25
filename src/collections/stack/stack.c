#include "stack.h"

#include "../error/lib_error.h"

Stack *st_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data), int (*compare_data)(void *data_1, void *data_2)) {
    return lk_create(free_data, copy_data, print_data, compare_data);
}

int st_push(Stack *stack, void *data) {
    return lk_add_index(stack, 0, data);
}

void *st_pop(Stack *stack) {
    return lk_remove_index(stack, 0);
}

void st_clear(Stack *stack) {
    lk_clear(stack);
}

int st_is_empty(Stack *stack) {
    if (!stack) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The queue does not exist");
        return 0;
    }

    return stack->size == 0;
}

void *st_get_head(Stack *stack) {
    return lk_get(stack, 0);
}

void
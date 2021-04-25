#include "queue.h"

#include "../error/lib_error.h"

Queue *qu_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data), int (*compare_data)(void *data_1, void *data_2)) {
    return lk_create(free_data, copy_data, print_data, compare_data);
}

int qu_push(Queue *queue, void *data) {
    return lk_add(queue, data);
}

void *qu_pop(Queue *queue) {
    return lk_remove_index(queue, 0);
}

void qu_clear(Queue *queue) {
    lk_clear(queue);
}

int qu_is_empty(Queue *queue) {
    if (!queue) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The queue does not exist");
        return 0;
    }

    return queue->size == 0;
}

void *qu_get_head(Queue *queue) {
    return lk_get(queue, 0);
}
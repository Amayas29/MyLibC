#ifndef QUEUE_H_
#define QUEUE_H_

#include "../linkedlist/linkedlist.h"

typedef LinkedList Queue;

Queue *qu_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data), int (*compare_data)(void *data_1, void *data_2));

int qu_push(Queue *queue, void *data);
void *qu_pop(Queue *queue);

void qu_clear(Queue *queue);

int qu_is_empty(Queue *queue);

void *qu_get_head(Queue *queue);

#endif
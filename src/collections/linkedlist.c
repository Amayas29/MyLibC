#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

#include "../error/lib_error.h"

LinkedList *lk_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data)) {
    if (!free_data || !copy_data || !print_data) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "Functions of data does not exist");
        return NULL;
    }

    LinkedList *linkedlist = malloc(sizeof(LinkedList));
    if (!linkedlist) {
        raise(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    linkedlist->_last = NULL;
    linkedlist->elements = NULL;
    linkedlist->size = 0;

    linkedlist->free_data = free_data;
    linkedlist->copy_data = copy_data;
    linkedlist->print_data = print_data;

    return linkedlist;
}

void lk_add(LinkedList *linkedlist, void *data) {
    if (!linkedlist) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    if (!data) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return;
    }

    Element *element = malloc(sizeof(Element));

    if (!element) {
        raise(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return;
    }

    element->data = data;
    element->next = NULL;

    if (linkedlist->_last) {
        linkedlist->_last->next = element;
        linkedlist->_last = element;
        return;
    }

    linkedlist->size++;
    linkedlist->_last = element;
    linkedlist->elements = element;
}

void lk_add_index(LinkedList *linkedlist, int index, void *data) {
    if (index < 0 || index >= linkedlist->size) {
        raise(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return;
    }

    Element *current = linkedlist->elements;
    for (; current && index > 0; current = current->next, index--) continue;

    if (!current && index > 0) {
        raise(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return;
    }

    Element *element = malloc(sizeof(Element));

    if (!element) {
        raise(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return;
    }

    // Add in head
    if (current == linkedlist->elements) {
        element->next = current;
        linkedlist->elements = element;

        linkedlist->size++;

        if (!linkedlist->_last)
            linkedlist->_last = element;

        return;
    }

    // If add in end : refresh last
    if (!current->next)
        linkedlist->_last = element;

    element->data = data;
    element->next = current->next;
    current->next = element;
    linkedlist->size++;
}

void lk_clear(LinkedList *linkedlist) {
    if (!linkedlist) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    linkedlist->size = 0;
    linkedlist->_last = NULL;

    Element *tmp = NULL;
    Element *curr = linkedlist->elements;
    while (curr) {
        tmp = curr->next;

        linkedlist->free_data(curr->data);
        free(curr);

        curr = tmp;
    }

    linkedlist->elements = NULL;
}

LinkedList *lk_clone(LinkedList *linkedlist) {
    if (!linkedlist) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    LinkedList *cloned = lk_create(linkedlist->free_data, linkedlist->copy_data, linkedlist->print_data);
    if (!cloned) return NULL;

    cloned->_last = NULL;

    for (Element *curr = linkedlist->elements; curr; curr = curr->next)
        lk_add(cloned, linkedlist->copy_data(curr->data));

    if (cloned->size != linkedlist->size) {
        lk_free(cloned);
        return NULL;
    }

    return cloned;
}

int lk_contains(LinkedList *linkedlist, void *data) {
    if (!linkedlist) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return 0;
    }

    if (!data) return 0;

    Element *curr = linkedlist->elements;
    for (; curr && curr->data != data; curr = curr->next) continue;

    return curr != NULL;
}

void *lk_get(LinkedList *linkedlist, int index) {
    if (!linkedlist) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    if (index < 0 || index >= linkedlist->size) {
        raise(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    Element *curr = linkedlist->elements;
    for (; curr && index > 0; curr = curr->next, index--) continue;

    if (curr) return curr->data;

    raise(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
    return NULL;
}

int lk_index_of(LinkedList *linkedlist, void *data) {
    if (!linkedlist) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return -1;
    }

    if (!data) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return -1;
    }

    Element *curr = linkedlist->elements;
    if (!curr) return -1;

    int index = 0;
    for (; curr && curr->data != data; curr->next, index++) continue;

    if (!curr) return -1;
    return index;
}

void *lk_remove_index(LinkedList *linkedlist, int index) {
    if (index < 0 || index >= linkedlist->size) {
        raise(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    Element *current = linkedlist->elements;
    for (; current && index > 0; current = current->next, index--) continue;

    if (!current && index > 0) {
        raise(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    // Remove in head
    if (current == linkedlist->elements) {
        Element *deleted = linkedlist->elements;
        linkedlist->elements = deleted->next;

        void *data = deleted->data;
        free(deleted);

        linkedlist->size--;

        if (!linkedlist->elements)
            linkedlist->_last = NULL;

        return data;
    }

    // If remove in end : refresh last
    if (!current->next)
        linkedlist->_last = NULL;  // TODO

    // TODO
    linkedlist->size--;
}

int lk_remove(LinkedList *linkedlist, void *data);
void *lk_set(LinkedList *linkedlist, int index, void *data);
LinkedList *lk_sub(LinkedList *linkedlist, int start, int end);
LinkedList *lk_filter(LinkedList *linkedlist, int (*property)(void *data));
void *lk_map(LinkedList *linkedlist, void (*map_fct)(void *data));
LinkedList *lk_quicksort(LinkedList *linkedlist, int (*compare)(void *data_1, void *data_2));

void lk_free(LinkedList *linkedlist) {
    if (!linkedlist) {
        raise(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    lk_clear(linkedlist);
    free(linkedlist);
}

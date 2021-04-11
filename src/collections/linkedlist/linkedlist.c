#include "linkedlist.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../error/lib_error.h"

static Element *el_quicksort(Element *head, Element *tail, int (*compare_data)(void *data_1, void *data_2));
static Element *el_partition(Element **liste, void *pivot, Element **end_left, Element **end_right, int (*compare_data)(void *data_1, void *data_2));

LinkedList *lk_create(void (*free_data)(void *data), void *(*copy_data)(void *data), void (*print_data)(void *data), int (*compare_data)(void *data_1, void *data_2)) {
    if (!free_data || !copy_data || !print_data || !compare_data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "Functions of data does not exist");
        return NULL;
    }

    LinkedList *linkedlist = malloc(sizeof(LinkedList));
    if (!linkedlist) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    linkedlist->_last = NULL;
    linkedlist->elements = NULL;
    linkedlist->size = 0;

    linkedlist->compare_data = compare_data;
    linkedlist->free_data = free_data;
    linkedlist->copy_data = copy_data;
    linkedlist->print_data = print_data;

    return linkedlist;
}

int lk_add(LinkedList *linkedlist, void *data) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return 0;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return 0;
    }

    Element *element = malloc(sizeof(Element));

    if (!element) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return 0;
    }

    element->data = data;
    element->next = NULL;
    linkedlist->size++;

    if (linkedlist->_last) {
        linkedlist->_last->next = element;
        linkedlist->_last = element;
        return 1;
    }

    linkedlist->_last = element;
    linkedlist->elements = element;
    return 1;
}

int lk_add_index(LinkedList *linkedlist, int index, void *data) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return 0;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return 0;
    }

    if (index < 0 || index > linkedlist->size) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return 0;
    }

    Element *current = linkedlist->elements;
    Element *pred = NULL;
    for (; current && index > 0; pred = current, current = current->next, index--) continue;

    if (!current && index > 0) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return 0;
    }

    Element *element = malloc(sizeof(Element));

    if (!element) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return 0;
    }

    element->data = data;

    // Add in head
    if (current == linkedlist->elements) {
        element->next = linkedlist->elements;
        linkedlist->elements = element;

        linkedlist->size++;

        if (!linkedlist->_last)
            linkedlist->_last = element;

        return 1;
    }

    // If add in end : refresh last
    if (!pred->next)
        linkedlist->_last = element;

    element->next = pred->next;
    pred->next = element;
    linkedlist->size++;
    return 1;
}

void lk_clear(LinkedList *linkedlist) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
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
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    LinkedList *cloned = lk_create(linkedlist->free_data, linkedlist->copy_data, linkedlist->print_data, linkedlist->compare_data);
    if (!cloned) return NULL;

    cloned->_last = NULL;

    for (Element *curr = linkedlist->elements; curr; curr = curr->next)
        if (!lk_add(cloned, linkedlist->copy_data(curr->data))) {
            lk_free(cloned);
            return NULL;
        }

    return cloned;
}

int lk_contains(LinkedList *linkedlist, void *data) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return 0;
    }

    if (!data) return 0;

    Element *curr = linkedlist->elements;
    for (; curr && linkedlist->compare_data(curr->data, data); curr = curr->next) continue;

    return curr != NULL;
}

void *lk_get(LinkedList *linkedlist, int index) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    if (index < 0 || index >= linkedlist->size) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    Element *curr = linkedlist->elements;
    for (; curr && index > 0; curr = curr->next, index--) continue;

    if (curr) return curr->data;

    raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
    return NULL;
}

int lk_index_of(LinkedList *linkedlist, void *data) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return -1;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return -1;
    }

    Element *curr = linkedlist->elements;
    if (!curr) return -1;

    int index = 0;
    for (; curr && linkedlist->compare_data(curr->data, data); curr = curr->next, index++) continue;

    if (!curr) return -1;
    return index;
}

void *lk_remove_index(LinkedList *linkedlist, int index) {
    if (index < 0 || index >= linkedlist->size) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    Element *current = linkedlist->elements;
    Element *pred = NULL;
    for (; current && index > 0; pred = current, current = current->next, index--) continue;

    if (!current && index > 0) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
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
        linkedlist->_last = pred;  // TODO

    pred->next = current->next;
    linkedlist->size--;
    void *data = current->data;
    free(current);
    return data;
}

int lk_remove(LinkedList *linkedlist, void *data) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return 0;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return 0;
    }

    if (!linkedlist->elements) return 1;

    if (linkedlist->compare_data(linkedlist->elements->data, data) == 0) {
        Element *deleted = linkedlist->elements;
        linkedlist->elements = deleted->next;
        linkedlist->size--;

        if (data != deleted->data)
            linkedlist->free_data(deleted->data);

        free(deleted);
        return 1;
    }

    Element *pred = linkedlist->elements;
    for (; pred->next && linkedlist->compare_data(pred->next->data, data); pred = pred->next) continue;

    if (!pred->next) return 0;

    linkedlist->size--;
    Element *deleted = pred->next;
    pred->next = deleted->next;
    if (data != deleted->data)
        linkedlist->free_data(deleted->data);
    free(deleted);
    return 1;
}

void *lk_set(LinkedList *linkedlist, int index, void *data) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return NULL;
    }

    if (index < 0 || index >= linkedlist->size) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    Element *curr = linkedlist->elements;
    for (; curr && index > 0; curr = curr->next, index--) continue;

    if (!curr) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    void *old_data = curr->data;
    curr->data = data;
    return old_data;
}

LinkedList *lk_sub(LinkedList *linkedlist, int start, int end) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return 0;
    }

    if (start < 0 || start >= linkedlist->size || end < 0) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    LinkedList *sub = lk_create(linkedlist->free_data, linkedlist->copy_data, linkedlist->print_data, linkedlist->compare_data);
    if (!sub) return NULL;

    if (end <= start) return sub;

    end -= start;

    Element *curr = linkedlist->elements;
    for (; curr && start > 0; curr = curr->next, start--) continue;

    if (!curr) {
        raise_error(IndexOutOfBoundsError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    for (; curr && end > 0; curr = curr->next, end--)
        if (!lk_add(sub, linkedlist->copy_data(curr->data))) {
            lk_free(sub);
            return NULL;
        }

    return sub;
}

LinkedList *lk_filter(LinkedList *linkedlist, int (*property)(void *data)) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return NULL;
    }

    if (!property) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The filter function does not exist");
        return NULL;
    }

    LinkedList *filtred = lk_create(linkedlist->free_data, linkedlist->copy_data, linkedlist->print_data, linkedlist->compare_data);
    if (!filtred) return NULL;

    for (Element *curr = linkedlist->elements; curr; curr = curr->next)
        if (property(curr->data))
            if (!lk_add(filtred, linkedlist->copy_data(curr->data))) {
                lk_free(filtred);
                return NULL;
            }

    return filtred;
}

int lk_map(LinkedList *linkedlist, void (*map_fct)(void *data)) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return 0;
    }

    if (!map_fct) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The map function does not exist");
        return 0;
    }

    for (Element *curr = linkedlist->elements; curr; map_fct(curr->data), curr = curr->next) continue;
    return 1;
}

void lk_quicksort(LinkedList *linkedlist) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    linkedlist->elements = el_quicksort(linkedlist->elements, linkedlist->_last, linkedlist->compare_data);
    Element *curr = linkedlist->elements;
    for (; curr; curr = curr->next) continue;
    linkedlist->_last = curr;
}

void lk_free(LinkedList *linkedlist) {
    if (!linkedlist) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The linkedlist does not exist");
        return;
    }

    lk_clear(linkedlist);
    free(linkedlist);
}

static Element *el_quicksort(Element *head, Element *tail, int (*compare_data)(void *data_1, void *data_2)) {
    if (!head || head == tail)
        return head;

    Element *end_left = NULL, *end_right = NULL;
    Element *left = el_partition(&head, tail->data, &end_left, &end_right, compare_data);

    Element *left_sorted = el_quicksort(left, end_left, compare_data);
    Element *right_sorted = el_quicksort(head, end_right, compare_data);

    if (!left_sorted) return right_sorted;
    if (!right_sorted) return left_sorted;

    Element *fusion = left_sorted;

    for (; left_sorted->next; left_sorted = left_sorted->next) continue;
    left_sorted->next = right_sorted;

    return fusion;
}

static Element *el_partition(Element **liste, void *pivot, Element **end_left, Element **end_right, int (*compare_data)(void *data_1, void *data_2)) {
    if (!*liste) return NULL;

    Element *left = NULL;
    Element *right = NULL;

    *end_left = NULL;
    *end_right = NULL;

    Element *curr = *liste;
    Element *tmp = NULL;

    while (curr) {
        tmp = curr->next;

        if (compare_data(curr->data, pivot) < 0) {
            if (!left)
                *end_left = curr;

            curr->next = left;
            left = curr;
            curr = tmp;
            continue;
        }
        if (!right)
            *end_right = curr;
        curr->next = right;
        right = curr;
        curr = tmp;
    }

    *liste = right;
    return left;
}

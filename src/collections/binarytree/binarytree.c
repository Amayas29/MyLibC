#include "binarytree.h"

#include <stdio.h>
#include <stdlib.h>

#include "../../error/lib_error.h"

Node *bt_create(void *data) {
    if (!data) {
        raise_error(NullPointerError, __FILE__, __FUNCTION__, __LINE__, "The data does not exist");
        return NULL;
    }

    Node *bt = malloc(sizeof(Node));

    if (!bt) {
        raise_error(AllocationError, __FILE__, __FUNCTION__, __LINE__, NULL);
        return NULL;
    }

    bt->data = data;
    bt->left_child = NULL;
    bt->right_child = NULL;

    return bt;
}
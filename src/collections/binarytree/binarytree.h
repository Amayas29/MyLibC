#ifndef BINARYTREE_H_
#define BINARYTREE_H_

typedef struct node {
    void *data;
    struct node *left_child;
    struct node *right_child;
} Node;

Node *bt_create(void *data);

#endif
#ifndef SEARCH_BINARYTREE_H
#define SEARCH_BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

typedef struct {
    Queue queue;
    QueueItem queueitem;
    int insert_order;
    char *node_name;
} TreeItem;

typedef struct treeNode *TreePointer;

typedef struct treeNode {
    TreeItem x;
    TreePointer right;
    TreePointer left;
} Tree;

void init_tree (TreePointer *tree) {
    (*tree) = NULL;
}

bool check_empty_tree (TreePointer *tree) {
    return ((*tree) == NULL);
}

int tree_depth (TreePointer *tree) {
    if ((*tree) == NULL)
        return 0;
    else {
        int leftDepth = tree_depth (&(*tree)->left);
        int rightDepth = tree_depth (&(*tree)->right);
        if (leftDepth > rightDepth)
            return leftDepth + 1;
        else
            return rightDepth + 1;
    }
}

int tree_size (TreePointer *tree) {
    if ((*tree) == NULL)
        return 0;
    else
        return (tree_size (&(*tree)->left) + 1 + tree_size (&(*tree)->right));
}

bool insert_tree (TreePointer *tree, TreeItem x) {
    if (check_empty_tree (&(*tree)) == true) {
        (*tree) = (Tree*) malloc (sizeof (Tree));
        (*tree)->right = (*tree)->left = NULL;
        (*tree)->x = x;
        return true;
    }
    else if (strcmp ((*tree)->x.node_name, x.node_name) == 0) {
        return false;
    }
    else if (strcmp ((*tree)->x.node_name, x.node_name) > 0) {
        return (insert_tree (&(*tree)->left, x));
    }
    else if (strcmp ((*tree)->x.node_name, x.node_name) < 0){
        return (insert_tree (&(*tree)->right, x));
    }
    else return false;
}

void search_insert_order (TreePointer *tree, int key, TreePointer *ret) {
    if ((*tree) == NULL) {
        return;
    }
    if ((*tree)->x.insert_order == key)
        (*ret) = (*tree);
    search_insert_order (&(*tree)->left, key, &(*ret));
    search_insert_order (&(*tree)->right, key, &(*ret));
}

void pre_order (TreePointer *tree) {
    if ((*tree) == NULL) {
        return;
    }
    printf ("%s: %i ", (*tree)->x.node_name, (*tree)->x.insert_order);
    pre_order (&(*tree)->left);
    pre_order (&(*tree)->right);
}

void post_order (TreePointer *tree) {
    if ((*tree) == NULL) {
        return;
    }
    post_order (&(*tree)->left);
    post_order (&(*tree)->right);
    printf ("%s: %i ", (*tree)->x.node_name, (*tree)->x.insert_order);
}

void in_order (TreePointer *tree) {
    if ((*tree) == NULL) {
        return;
    }
    in_order (&(*tree)->left);
    printf ("%s: %i ", (*tree)->x.node_name, (*tree)->x.insert_order);
    in_order (&(*tree)->right);
}

bool search_tree (TreePointer *tree, char *key, TreeItem *ret) {
    if ((*tree) == NULL)
        return false;
    if (strcmp ((*tree)->x.node_name, key) == 0) {
        *ret = (*tree)->x;
        return true;
    }
    if (strcmp ((*tree)->x.node_name, key) < 0)
        return search_tree (&(*tree)->left, key, ret);
    else
        return search_tree (&(*tree)->right, key, ret);
}

TreePointer get_min (TreePointer *tree) {
    TreePointer aux;
    if ((*tree)->left == NULL) {
        aux = (*tree);
        (*tree) = (*tree)->right;
        return aux;
    }
    else
        return get_min (&(*tree)->left);
}

TreePointer get_max (TreePointer *tree) {
    TreePointer aux;
    if ((*tree)->right == NULL) {
        aux = (*tree);
        (*tree) = (*tree)->left;
        return aux;
    }
    else
        return get_max (&(*tree)->right);
}

bool remove_tree (TreePointer *tree, char *key) {
    if ((*tree) == NULL)
        return false;
    else if (strcmp ((*tree)->x.node_name, key) == 0) {
        TreePointer aux;
        aux = (*tree);
        if (((*tree)->left == NULL) && ((*tree)->right == NULL))
            (*tree) = NULL;
        else if ((*tree)->left == NULL)
            (*tree) = (*tree)->right;
        else if ((*tree)->right == NULL)
            (*tree) = (*tree)->left;
        else {
            aux = get_min(&(*tree)->right);
            (*tree)->x = aux->x;
        }
        free (aux);
        return true;
    }
    else if (strcmp ((*tree)->x.node_name, key) < 0)
        return remove_tree (&(*tree)->left, key);
    else
        return remove_tree (&(*tree)->right, key);
}

char *tree_max (TreePointer *tree) {
    if ((*tree)->right == NULL)
        return (*tree)->x.node_name;
    else
        return tree_max (&(*tree)->right);
}

char *tree_min (TreePointer *tree) {
    if ((*tree)->left == NULL)
        return (*tree)->x.node_name;
    else
        return tree_min (&(*tree)->left);
}

void destroy_tree (TreePointer *tree) {
    if ((*tree) == NULL) {
        return;
    }
    destroy_tree (&(*tree)->left);
    destroy_tree (&(*tree)->right);
    remove_tree(&(*tree), (*tree)->x.node_name);
}

#endif //SEARCH_BINARYTREE_H

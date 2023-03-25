#ifndef avl_h
#define avl_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int key;
} avl_Item;

typedef struct TreeNode *avl_ptr;

typedef struct TreeNode {
    avl_Item item;
    avl_ptr left;
    avl_ptr right;
    int depth;
} TreeNode;

void init_avl (avl_ptr *node) {
    (*node) = NULL;
}

bool check_empty_avl (avl_ptr *node) {
    return (*node) == NULL;
}

int avl_depth (avl_ptr *node) {
    if ((*node) == NULL)
        return 0;
    else {
        int left_depth = avl_depth (&(*node)->left);
        int right_depth = avl_depth (&(*node)->right);
        if (left_depth > right_depth)
            return left_depth + 1;
        else
            return right_depth + 1;
    }
}

void update_depth (avl_ptr *node) {
    if(check_empty_avl (node) == true)
        return;
    else{
        (*node)->depth = avl_depth (node);
        update_depth (&(*node)->left);
        update_depth (&(*node)->right);
    }
}

void simple_right_rotation (avl_ptr *node) {
    avl_ptr u = (*node)->left;
    (*node)->left = u->right;
    u->right = (*node);
    update_depth (&u);
    update_depth (node);
    (*node) = u;
}

void simple_left_rotation (avl_ptr *node) {
    avl_ptr u = (*node)->right;
    (*node)->right = u->left;
    u->left = (*node);
    update_depth (&u);
    update_depth (node);
    (*node) = u;
}

void double_right_rotation (avl_ptr *node) {
    avl_ptr u = (*node)->left;
    avl_ptr v = u->right;
    u->right = v->left;
    v->left = u;
    (*node)->left = v->right;
    v->right = (*node);
    update_depth (&u);
    update_depth (&v);
    update_depth (node);
    (*node) = v;
}

void double_left_rotation (avl_ptr *node) {
    avl_ptr u = (*node)->right;
    avl_ptr v = u->left;
    (*node)->right = v->left;
    u->left = v->right;
    v->right = u;
    v->left = (*node);
    update_depth  (&u);
    update_depth (&v);
    update_depth (node);
    (*node) = v;
}

void apply_rotation (avl_ptr *node) {
    int bar = avl_depth (&(*node)->right) - avl_depth (&(*node)->left);
    if (abs (bar) > 1) {
        if (bar < 0) {
            if (avl_depth (&(*node)->left->left) >= avl_depth (&(*node)->left->right))
                simple_right_rotation (node);
            else
                double_right_rotation (node);
        } else if (avl_depth (&(*node)->right->left) > avl_depth (&(*node)->right->right))
            double_left_rotation (node);
        else
            simple_left_rotation (node);
    }
}

bool avl_insert (avl_ptr *node, avl_Item item) {
    bool aux;
    if ((*node) == NULL){
        (*node) = (avl_ptr) malloc (sizeof (TreeNode));
        (*node)->right = (*node)->left = NULL;
        (*node)->item = item;
        (*node)->depth = 0;
        return true;
    } else if ((*node)->item.key == item.key)
        return false;
    else if ((*node)->item.key > item.key)
        aux = avl_insert (&(*node)->left, item);
    else
        aux = avl_insert (&(*node)->right, item);

    if (aux) {
        apply_rotation (node);
        update_depth (node);
        return true;
    }
    else
        return false;
}

avl_ptr get_max (avl_ptr *node) {
    if ((*node)->right != NULL)
        return get_max (&(*node)->right);
    return (*node);
}

bool avl_remove (avl_ptr *node, int key) {
    bool aux2;
    if ((*node) == NULL)
        return false;

    else if ((*node)->item.key == key){
        avl_ptr aux = (*node);

        if ((*node)->right == NULL && (*node)->left == NULL)
            (*node) = NULL;

        else if ((*node)->left == NULL)
            (*node) = (*node)->right;

        else if ((*node)->right == NULL)
            (*node) = (*node)->left;

        else {
            (*node) = get_max (&(*node)->left);
            (*node)->right = aux->right;
        }
        free(aux);
        return true;
    }
    else if ((*node)->item.key > key)
        aux2 = avl_remove (&(*node)->left, key);
    else
        aux2 = avl_remove (&(*node)->right, key);
    if (aux2) {
        apply_rotation (node);
        update_depth (node);
        return true;
    }
    else return false;
}

void avl_destroy (avl_ptr *node) {
    if((*node) != NULL){
        avl_destroy (&(*node)->left);
        avl_destroy (&(*node)->right);
        avl_remove (&(*node), (*node)->item.key);
    }
}

void print_level (avl_ptr *node, int level, FILE *a) {
    if ((*node) == NULL)
        return;
    else if (level == 1) {
        int bal = 0;
        bal = avl_depth (&(*node)->right) - avl_depth (&(*node)->left);
        fprintf(a, "%i (%i), ", (*node)->item.key, bal);
    }
    else {
        print_level (&(*node)->left, level - 1, a);
        print_level (&(*node)->right, level - 1, a);
    }
}

void level_print (avl_ptr *node, FILE *a) {
    for (int i = 1; i <= avl_depth (&(*node)); i ++) {
        print_level (&(*node), i, a);
        fprintf (a, "\n");
    }
}

#endif
#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct List_Node *List_Pointer;

typedef struct List_Node {
    int vertex_index;
    List_Pointer next;
} dList;

typedef struct {
    List_Pointer st;
    int size;
}List;

void init_list (List *list) {
    list->st = NULL;
    list->size = 0;
}

bool list_search (List *list, int x) {
    if  (list->size == 0) {
        return 0;
    } else {
        List_Pointer aux;
        aux = list->st;
        while ((aux != NULL) && (x > aux->vertex_index)) {
            aux = aux->next;
        }
        if ((aux == NULL) || (aux->vertex_index > x)) {
            return false;
        } else {
            return true;
        }
    }
}

bool list_insert (List *list, int x) {
    List_Pointer new;
    new = (List_Pointer) malloc (sizeof (dList));
    new->vertex_index = x;
    if (list_search (list, x) == true) return false;
    else if ((list->size == 0) || (x < list->st->vertex_index)) {
        new->next = list->st;
        list->st = new;
        list->size++;
        return true;
    }
    else {
        List_Pointer a;
        a = list->st;
        while (a->next != NULL && x > a->vertex_index) {
            a = a->next;
        }
        new->next = a->next;
        a->next = new;
        list->size++;
        return true;
    }
}

int list_remove (List *list, int key) {
    if ((list->size == 0) || (key < list->st->vertex_index)) {
        return 0;
    }
    if (key == list->st->vertex_index) {
        List_Pointer aux;
        aux = list->st;
        list->st = list->st->next;
        free (aux);
        list->size--;
        return 1;
    }
    List_Pointer aux;
    aux = list->st;
    while ((aux->next != NULL) && key > aux->next->vertex_index)
        aux = aux->next;

    if ((aux->next == NULL) || (key < aux->next->vertex_index)) {
        return 0;
    } else {
        List_Pointer rmv;
        rmv = aux->next;
        aux->next = aux->next->next;
        free (rmv);
        list->size--;
        return 1;
    }
}
void print_list (List *list) {
    List_Pointer aux;
    if (list->size == 0)
        printf ("Lista vazia\n");
    else {
        for (aux = list->st; aux != NULL; aux = aux->next) {
            printf("%i ", aux->vertex_index);
        }
        printf("\n");
    }
}
void destroy_list (List *list) {
    List_Pointer rmv;
    while (list->st != NULL) {
        rmv = list->st;
        list->st = list->st->next;
        free (rmv);
    }
}

#endif //GRAPH_LIST_H

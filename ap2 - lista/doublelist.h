#ifndef UNTITLED_DOUBLELIST_H
#define UNTITLED_DOUBLELIST_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct  {
    int key;
} Item;

typedef struct lNode *Pointer;

typedef struct lNode {
    Item x;
    Pointer next;
    Pointer prev;
} lNode;

typedef struct {
    Pointer first;
    Pointer last;
    int size;
} List;

void lInit (List *list) {
    list->first = NULL;
    list->size = 0;
}

bool checkIfEmpty (List *list) {
    return (list->size == 0);
}

bool insert (List *list, Item x) {
    Pointer new;
    new = (Pointer) malloc (sizeof (lNode));
    new->x = x;
    if (checkIfEmpty (list) == true) {
        new->next = NULL;
        new->prev = NULL;
        list->first = new;
        list->last = new;
    }
    else if (x.key < list->first->x.key) {
        list->first->prev = new;
        new->next = list->first;
        new->prev = NULL;
        list->first = new;
    }
    else if (x.key > list->last->x.key) {
        list->last->next = new;
        new->prev = list->last;
        new->next = NULL;
        list->last = new;
    }
    else {
        Pointer aux;
        for (aux = list->first; aux->next != NULL && x.key > aux->next->x.key; aux = aux->next);
        new->next = aux->next;
        new->prev = aux;
        aux->next = new;
    }
    list->size ++;
    return true;
}

bool lSearch (List *list, int key) {
    Pointer aux;
    for(aux = list->first; aux != NULL; aux = aux->next){
        if(aux->x.key == key)
            return true;
    }
    return false;
}

bool rmv (List *list, int key) {
    if (checkIfEmpty (list) == true || key < list->first->x.key)
        return false;
    else if (key == list->first->x.key) {
        Pointer aux;
        aux = list->first;
        list->first = list->first->next;
        free (aux);
        list->size --;
        return true;
    }
    else {
        Pointer run;
        for (run = list->first; run->next != NULL && run->next->x.key != key; run = run->next);
        if (run->next == NULL)
            return false;
        else {
            Pointer aux;
            aux = run->next;
            run->next = aux->next;
            if (aux->x.key == list->last->x.key)
                list->last = run;
            free (aux);
            list->size --;
            return true;
        }
    }
}

void lPrint (List *list) {
    if (checkIfEmpty (list) == true)
        printf ("Sem itens na lista!\n");
    else {
        Pointer aux;
        printf ("\nLista em ordem crescente: ");
        for (aux = list->first; aux != NULL; aux = aux->next) {
            printf("%i ", aux->x.key);
        }
        printf("\n\n");
    }
}

void reverse_print (List *list) {
    if (checkIfEmpty (list) == true)
        printf ("Sem itens na lista!\n");
    else {
        Pointer aux;
        printf ("\nLista em ordem decrescente: ");
        for (aux = list->last; aux != NULL; aux = aux->prev) {
            printf("%i ", aux->x.key);
        }
        printf("\n\n");
    }
}

int lSize (List *list) {
    return list->size;
}

void lDestroy (List *list) {
    Pointer aux;
    for (aux = list->last; aux != NULL; aux = aux->prev) {
        rmv (list, aux->x.key);
    }
}

Item first (List *list) {
    return list->first->x;
}

Item last (List *list) {
    return list->last->x;
}

bool removeFirst (List *list) {
    rmv(list, first (list).key);
    return true;
}

bool removeLast (List *list) {
    rmv(list, last (list).key);
    return true;
}

#endif //UNTITLED_DOUBLELIST_H


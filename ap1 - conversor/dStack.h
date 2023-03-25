#ifndef UNTITLED_DSTACK_H
#define UNTITLED_DSTACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
} dItem;

typedef struct NoPilha *Ponteiro;

typedef struct NoPilha{
    dItem item;
    Ponteiro proximo;
} StackNode;

typedef struct {
    Ponteiro topo;
    int tamanho;
} dStack;

void dInit (dStack *pilha) {
    pilha->topo = NULL;
    pilha->topo = 0;
    pilha->tamanho = 0;
}

int dEmpty (dStack *pilha) {
    return (pilha->tamanho == 0);
}

void dPush (dItem item, dStack *pilha) {
    Ponteiro aux;
    aux = (Ponteiro) malloc (sizeof (StackNode));
    aux->item = item;
    aux->proximo = pilha->topo;
    pilha->topo = aux;
    pilha->tamanho ++;
    //printf ("Empilhou: %d\n-----------------------------\n", aux->item.key);
}

void dPop (dStack *pilha, dItem *item) {
    if (dEmpty(pilha))
        printf("Pilha vazia!!");
    else {
        *item = pilha->topo->item;
        Ponteiro aux;
        aux = pilha->topo;
        //printf ("Desempilhou: %d\n-----------------------------\n", aux->item.key);
        pilha->topo = pilha->topo->proximo;
        free(aux);
        pilha->tamanho--;
    }
}

int dSize (dStack *pilha) {
    return (pilha->tamanho);
}

dItem dTop (dStack *pilha, dItem *item) {
    *item = pilha->topo->item;
    return *item;
}

void dPrint (dStack *pilha) {
    Ponteiro aux;
    printf ("\nEstado atual da pilha: ");
    for (aux = pilha->topo; aux != NULL; aux = aux->proximo)
        printf ("%d ", aux->item.key);
    printf ("\n-----------------------------------------\n");
    printf("\n");
}

#endif //UNTITLED_DSTACK_H

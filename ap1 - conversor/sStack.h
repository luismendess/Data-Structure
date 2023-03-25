#ifndef UNTITLED_SSTACK_H
#define UNTITLED_SSTACK_H

#include <stdio.h>
#define N 100

typedef struct {
    int key;
} sItem;

typedef struct {
    sItem array[N];
    int top;
} sStack;

void sInit(sStack *pilha){
    pilha->top = 0;
}
int sEmpty(sStack *pilha){
    return (pilha->top == 0);
}
int sFull(sStack *pilha) {
    return (pilha->top == N);
}
void sPush(sItem item, sStack *pilha) {
    if (sFull(pilha) == 0) {
        pilha->array[pilha->top] = item;
        pilha->top++;
    }
    else
        printf ("Pilha cheia\n");
}
void sPop(sStack *pilha, sItem *item) {
    if (sEmpty(pilha) == 0) {
        *item = pilha->array[pilha->top - 1];
        pilha->top--;
    }
    else
        printf ("Pilha vazia\n");
}
int sSize(sStack *pilha) {
    return (pilha->top);
}
sItem sTop(sStack *pilha) {
    return (pilha->array[pilha->top - 1]);
}
void sPrint(sStack *pilha) {
    printf ("Estado atual da pilha:\n");
    for (int i = 0; i < pilha->top; i++){
        printf ("%d ", pilha->array[i].key);
    }
    printf ("\n");
}

#endif //UNTITLED_SSTACK_H

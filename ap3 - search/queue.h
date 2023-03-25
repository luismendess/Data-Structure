#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int key;
} QueueItem;

typedef struct QueueNode *QueuePointer;

typedef struct QueueNode{
    QueueItem x;
    QueuePointer next;
} QueueNode;

typedef struct {
    QueuePointer start;
    QueuePointer end;
    int size;
} Queue;

void init_queue (Queue *queue) {
    queue->start = queue->end = NULL;
    queue->size = 0;
}

int queue_size (Queue *queue) {
    return queue->size;
}

bool check_empty_queue (Queue *queue) {
    return queue_size (queue) == 0;
}

void enqueue (QueueItem x, Queue *queue) {
    QueuePointer aux;
    aux = (QueuePointer) malloc (sizeof (QueuePointer));
    aux->x = x;
    aux->next = NULL;
    if (check_empty_queue (queue) == true) {
        queue->start = queue->end = aux;
        queue->size ++;
    }
    else {
        queue->end->next = aux;
        queue->end = aux;
        queue->size ++;
    }
}

void dequeue (Queue *queue) {
    QueuePointer aux;
    aux = queue->start;
    if (queue_size (queue) == 1) {
        queue->start = queue->end = NULL;
        queue->size --;
    } else {
        queue->start = queue->start->next;
        queue->size --;
    }
    free (aux);
}

void print_queue (FILE *file, Queue *queue) {
    QueuePointer aux;
    if (check_empty_queue (queue) == true)
        printf ("Lista vazia");
    else {
        for (aux = queue->start; aux != NULL; aux = aux->next) {
            fprintf(file, ",%i", aux->x.key);
        }
    }
}

QueueItem queue_start (Queue *queue) {
    QueueItem x;
    x = queue->start->x;
    return x;
}

QueueItem queue_end (Queue *queue) {
    QueueItem x;
    x = queue->end->x;
    return x;
}

#endif /* queue_h */
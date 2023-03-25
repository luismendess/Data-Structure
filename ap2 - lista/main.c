#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "doublelist.h"

int main() {
    List l;
    lInit(&l);
    Item x;
    x.key = 7;
    insert (&l, x);
    x.key = 35;
    insert (&l, x);
    x.key = 5;
    insert (&l, x);
    x.key = 70;
    insert (&l, x);
    x.key = -3;
    insert (&l, x);
    x.key = 98;
    insert (&l, x);
    lPrint (&l);
    //reverse_print (&l);
    printf ("Primeiro item da lista: %i\n", first (&l).key);
    printf ("Ultimo item da lista: %i\n", last (&l).key);
    //removeFirst (&l);
    lPrint (&l);
    reverse_print (&l);
    printf ("%i\n", l.first->next->x.key);
    removeLast (&l);
    removeFirst (&l);
    printf ("%i\n", l.last->prev->x.key);
    if (lSearch (&l, 70) == true) {
        printf ("O elemento esta na lista\n");
    }
    if (lSearch (&l, 46) == false) {
        printf ("O elemento nao esta na lista\n");
    }
    return 0;
}
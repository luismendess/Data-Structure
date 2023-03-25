#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "graph.h"

int main() {
    int size = 5, from, to, opt;
    Vertex *grafo;
    grafo = (Vertex*) malloc (size * sizeof (Vertex));
    init_graph (grafo, size);
    do {
        printf ("\nEscolha uma opcao:\n1 - Criar nova adjacencia.\n2 - Encerrar\n"); scanf ("%i", &opt);
        if (opt == 1) {
            printf ("Vertice de origem:"); scanf ("%i", &from);
            printf ("Vertice de destino:"); scanf ("%i", &to);
            grafo[from - 1].adjacence_matrix[from - 1][to - 1] = 1;
            list_insert (&grafo[from - 1].adjacence_list, to);
        } else if (opt == 2) {
            print_graph_list (grafo, size);
        }
        else printf ("\nOpcao invalida\n");
    } while (opt != 2);
    for (int i = 0; i < size; i++)
        destroy_list (&grafo[i].adjacence_list);
    free (grafo);
    return 0;
}
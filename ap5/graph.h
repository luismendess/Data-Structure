#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

typedef struct Vertex {
    int key;                            //nome do vertice
    int visited;                        //cor
    int closure;                        //tempo de fechamento
    int discovery;                      //tempo de descobrimento
    List adjacence_list;                //lista de adjacencia
    int parent;                         //vértice pai
    int adjacent_vertices;              //quantidade de vértices adjacentes
    int **adjacence_matrix;             //matriz de adjacencia
} Vertex;

void init_graph (Vertex *vertex, int size) {
    for (int i = 0; i < size; ++i) {
        vertex[i].adjacence_matrix = (int**) malloc (size * sizeof (int*));
        for (int j = 0; j < size; ++j) {
            vertex[i].adjacence_matrix[i] = (int*) malloc (size * sizeof (int));
        }
        init_list (&vertex[i].adjacence_list);
        vertex[i].key = i + 1;
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            vertex[i].adjacence_matrix[i][j] = 0;
        }
    }
}

void print_graph_list (Vertex *vertex, int d) {
    for (int i = 0; i < d; i++) {
        printf("\nIndice do vertice: %i\nVertices ligantes: ", vertex[i].key);
        print_list(&vertex[i].adjacence_list);
        printf("\n");
    }
}

void print_graph_matrix (Vertex *vertex, int d) {
    for (int i = 0; i < d; i++) {
        printf("\nIndice do vertice: %i\nVertices ligantes: ", vertex[i].key);
        for (int j = 0; j < d; j++) {
            if (vertex[i].adjacence_matrix[i][j] == 1)
                printf ("%i ", j + 1);
        }
        printf ("\n");
    }
}

#endif //GRAPH_GRAPH_H

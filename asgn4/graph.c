//Derick Pan
//dpan7
//Asgn4

#include "graph.h"

#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Graph {
    uint32_t vertices; //Number of vertices
    bool undirected; //Undirected Graph?
    bool visited[VERTICES]; //Where have we gone?
    uint32_t matrix[VERTICES][VERTICES]; //Adjacency Matrix
} Graph;

Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) malloc(sizeof(Graph));
    if (G) {
        G->vertices = vertices;
        G->undirected = undirected;

        for (uint32_t i = 0; i < G->vertices; i++) {
            G->visited[i] = false; //Index of visited is false
            for (uint32_t j = 0; j < G->vertices; j++) {
                G->matrix[i][j] = 0; //Each cell is set to zero
            }
        }
    }
    return G;
}

void graph_delete(Graph **G) {
    if (*G) {
        free((*G));
        *G = NULL;
    }
    return;
}

//Return Number of vertices in graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    /*				### Can there be undirected?
	if(i < VERTICES && j < VERTICES){			//If in bound, add
		G->matrix[i][j] =k;
	}
	*/
    G->matrix[i][j] = k; //Directed
    if (G->undirected && i < G->vertices
        && j < G->vertices) { //If it's undirected and in bound then add
        G->matrix[j][i] = k;
        //G->matrix[i][j] = k;
        return true;
    }
    return true;
}

//Return True if i & j within bound and has edge
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {

    if (i < G->vertices && j < G->vertices && G->matrix[i][j] > 0) {
        return true;
    }
    return false;
}

//Return weight of edge
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {

    if (graph_has_edge(G, i, j)) {
        return G->matrix[i][j];
    }
    return 0;
}

//Return true if vertex v has been visited
bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

//If Vertex V is within bounds, mark V as visited
void graph_mark_visited(Graph *G, uint32_t v) {

    uint32_t counter = 0;
    for (uint32_t i = 0; i < G->vertices; i++) { //Iterate over I
        for (uint32_t j = 0; j < G->vertices; j++) { //Iterate over J
            if (graph_has_edge(G, i, j)) { //If there is an edge
                counter++; //Then add 1 to counter
            }
            if (counter == v && graph_has_edge(G, i, j)) {
                G->visited[v] = true; //Mark visited
            }
        }
    }
}

//If Vertex V is within bounds, mark V as unvisited
void graph_mark_unvisited(Graph *G, uint32_t v) {
    uint32_t counter = 0;
    for (uint32_t i = 0; i < G->vertices; i++) { //Iterate over I
        for (uint32_t j = 0; j < G->vertices; j++) { //Iterate over J
            if (graph_has_edge(G, i, j)) { //If there is an edge
                counter++; //Then add 1 to counter
            }
            if (counter == v && graph_has_edge(G, i, j)) {
                G->visited[v] = false; //Mark Unvisited
            }
        }
    }
}

void graph_print(Graph *G) {

    for (uint32_t i = 0; i < G->vertices; i++) { //Iterate over I
        for (uint32_t j = 0; j < G->vertices; j++) { //Iterate over J
            printf("%u ", G->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//Derick Pan
//dpan7
//Asgn4

#include "graph.h"
#include "vertices.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Graph {
	uint32_t vertices;			//Number of vertices
	bool undirected;			//Undirected Graph?
	bool visited[VERTICES];		//Where have we gone?
	uint32_t matrix[VERTICES][VERTICES];	//Adjacency Matrix
}	Graph;


Graph *graph_create(uint32_t vertices, bool undirected) {
	Graph *G = (Graph *) malloc(sizeof(Graph));
	if (G) {
		G->vertices = vertices;
		G->undirected =	undirected;

		for (uint32_t i =0; i<=vertices; i++) {
			G->visited[VERTICES] = false;		//Index of visited is false
			for (uint32_t j=0; j<=vertices; j++) {
				G->matrix[i][j] =0;   			//Each cell is set to zero
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

uint32_t graph_vertices(Graph *G) {  //Return Number of vertices in graph
	return G->vertices;
}


bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {

	if (G->undirected && G->matrix[j][i] != NULL ) {
		G->matrix[j][i] = k;
	}

	if(G->matrix[i][j] != NULL){
		G->matrix[i][j] ==k;
	}


	//add edge
	//weight k from j to i




}

bool graph_has_edge(Graph *G, uint32_t i, uint32_t j);

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j);

bool graph_visited(Graph *G, uint32_t v);

void graph_mark_visited(Graph *G, uint32_t v);

void graph_mark_unvisited(Graph *G, uint32_t v);

void graph_print(Graph *G);

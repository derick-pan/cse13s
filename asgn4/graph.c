//Derick Pan
//dpan7
//Asgn4

#include "graph.h"
#include "vertices.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Graph {
	uint32_t vertices;
	bool undirected;
	bool visited[VERTICES];
	uint32_t matrix[VERTICES][VERTICES];
}	Graph;

Graph *graph_create(uint32_t vertices, bool undirected) {
	
	Graph *G = (Graph *) malloc(sizeof(Graph));
	if (G) {
		G->vertices = vertices;
		G->undirected =	undirected;
		G->visited[VERTICES] = false;
	        G->matrix[VERTICES][VERTICES] = 0;	

		for (int i =0; i<=vertices; i++) {
			G->visted[VERTICES] = false;		
			for (int j=0; j<=vertices; j++) {
				G->matrix[i][j] =0;	
			}	
		}
	}
	return G;
}




void graph_delete(Graph **G) {
	if (*g) {
		free((*G);
		*G = NULL;
	}
	return;
}

uint32_t graph_vertices(Graph *G) {
	return G->vertices;
}
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {

	if (g->undirected && g->matrix[j][i] != NULL ) {
		g->matrix[j][i] = k;
	}

	if(g->matrix[i][j] != NULL){
		g->matrix[i][j] ==k;
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


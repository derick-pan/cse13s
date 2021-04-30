//Derick Pan
//dpan7
//Asgn4

#include "path.h"

#include "graph.h"
#include "stack.h"
#include "vertices.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Path {
    Stack *vertices; //Vertices comprising path
    uint32_t length;
} Path;

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));

    p->vertices = stack_create(VERTICES);
    p->length = 0;

    return p;
}

void path_delete(Path **p) {
    if (*p && (*p)->vertices) {
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    uint32_t x;
    if (stack_full(p->vertices)) {
        printf("Can not path Push Vertex  \n");
        return false;
    } else if (stack_empty(p->vertices)) { //If the stack is empty push it, and length is 0,v
        stack_push(p->vertices, v);
        p->length += graph_edge_weight(G, START_VERTEX, v);
        return true;
    }
    stack_peek(p->vertices, &x);
    stack_push(p->vertices, v);
    p->length += graph_edge_weight(G, x, v);
    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) {
        return false;
    } else {
        uint32_t x = 0;
        stack_pop(p->vertices, v);
        stack_peek(p->vertices, &x); //Gets the vertex at top of the stack

        p->length -= graph_edge_weight(G, x, *v);
        return true;
    }
}

//returns number of vertices in the path
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices); //returns next empty position
}

//returns the length of the path
uint32_t path_length(Path *p) {
    return p->length; //Returns current length
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {

    stack_print(p->vertices, outfile, cities);
}

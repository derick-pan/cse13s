//Derick Pan
//dpan7
//Asgn4

#include "path.h"
#include "graph.h"
#include "stack.h"
#include "vertices.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Path {
    Stack *vertices;  //Vertices comprising path
    uint32_t length;
} Path;

Path *path_create(void){
    Path *p = (Path *) malloc(sizeof(Path));

    Stack *vertices = stack_create(VERTICES);
    p->length = 0;

    return p;
}

void path_delete(Path **p);

bool path_push_vertex(Path *p, uint32_t v, Graph *G);

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G);

uint32_t path_vertices(Path *p);

uint32_t path_length(Path *p);

void path_copy(Path *dst, Path *src);

void path_print(Path *p, FILE *outfile, char *cities[]);

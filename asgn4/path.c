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

    p->vertices = stack_create(VERTICES);
    p->length = 0;

    return p;
}

void path_delete(Path **p){
    if (*p && (*p)->vertices) {
        free((*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G){

    if (stack_full(p->vertices)){
        return false;
    }
    stack_push(p->vertices , v); //Push vertex v onto path p *vertices
    p->length += v;

    return true;
    //Length of path is increased by edge weight
    //Return True if vertex was successfully pushed and false otherwise

}

/*What G for ? */
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G){
    uint32_t x= *v;

    if (!stack_empty(p->vertices)){

        stack_pop(p->vertices, &x);
        p->length -= x;
        *v = x;
        return true;

    }
    return false;
}
//returns number of vertices in the path
uint32_t path_vertices(Path *p);


//returns the length of the path
uint32_t path_length(Path *p);

void path_copy(Path *dst, Path *src);

void path_print(Path *p, FILE *outfile, char *cities[]);

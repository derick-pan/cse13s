//Derick Pan
//dpan7
//Asgn4
#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main() {
    Graph *G = graph_create(6, true);
    graph_add_edge(G, 0, 1, 10);
    graph_add_edge(G, 1, 2, 2);
    graph_add_edge(G, 1, 3, 5);
    graph_add_edge(G, 2, 5, 3);
    graph_add_edge(G, 2, 25, 5);
    graph_add_edge(G, 3, 4, 21);
    graph_print(G);
    printf("\n");
	Path *p = path_create();
    path_push_vertex(p, 0, G);
    printf ("0Path Length: %u\n", path_length(p));  //0

	path_push_vertex(p, 1, G);
    printf ("1Path Length: %u\n", path_length(p)); //10

    path_push_vertex(p, 2, G);
    printf ("2Path Length: %u\n", path_length(p)); //10

    FILE * outfile = fopen("outfile.txt", "w");
    char *cities[] = {"Alabama", "wisconsin", "depression", "california"};
    path_print(p, outfile, cities);
    fclose(outfile);
    printf ("Amount of vertices: %u\n", path_vertices(p)); //3
    Path *q = path_create();
    path_copy(q, p);
    printf ("2Path Length: %u\n", path_length(q)); //10
    path_delete(&p);

    graph_delete(&G);
}


    Path *curr = path_create();
    Path *short = path_create();

    void dfs(Path *curr, Path *short, Graph *G, uint32_t v){
        graph_mark_visited(G,v);
        uint32_t x;
        if (path_length(curr) < path_length(short)){
            path_copy(short,curr);
        }

        for (uint32_t w=0; w< VERTICES; w++){
            if (graph_has_edge(G,v,w)){ //Only edges
                if (!graph_visited(G,w)){ //If not visited,
                    path_push_vertex(p,w,G);   //Push it onto the stack
                    dfs(curr,short,G,w);       //test it recursively
                    path_pop_vertex(p,&x,G);   //Pop the stack after testing all of dfs
                } //If all visited then it stops
                dfs(curr,short,G,w);

            }
        }
        graph_mark_unvisited(G,v);
    }

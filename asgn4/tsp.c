// Derick Pan
// dpan7
// Asgn4
#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
char usage[1000] = "SYNOPSIS\n\
  Traveling Salesman Problem using DFS.\n\n\
USAGE\n\
  ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n\n\
OPTIONS\n\
  -u             Use undirected graph.\n\
  -v             Enable verbose printing.\n\
  -h             Program usage and help.\n\
  -i infile      Input containing graph (default: stdin)\n\
  -o outfile     Output of computed path (default: stdout)\n";

int recursetimes = 0;
int flagham;
bool verbose = false;
void dfs(Graph *G, uint32_t v, Path *c, Path *s,FILE* outfile,char *cities[]) {
    flagham = 0;

    graph_mark_visited(G, v);

    for (uint32_t q = 0; q < graph_vertices(G); q++) {
        if (!graph_visited(G, q)) {
            flagham = 1; // If flagham ==1 then SOME POINT is not visited
            break;
        }
    }
    uint32_t x = 0;
    if (flagham == 0) {
        if (path_vertices(s) == 0 && graph_has_edge(G, v, 0)) { //This if statement seems fine
            //          fprintf(outfile, "I'm a solo\n");
            path_push_vertex(c, START_VERTEX, G); //Push in the return to origin
            path_copy(s, c);
            path_pop_vertex(c, &x, G); //Pop the return to origin
            // path_print(s, outfile, cities);
        }
        if (graph_has_edge(G, v, 0)) { //Now i can test it
            path_push_vertex(c, START_VERTEX, G); //Push in the return to origin
            if (path_length(c) < path_length(s)) {
                path_copy(s, c);
		if (verbose == true){
		   fprintf(outfile, "Path Length: %u\n", path_length(s));
                   path_print(s, outfile, cities);
		}

                //			fprintf(outfile, "~");
            }
            path_pop_vertex(c, &x, G); //Pop the return to origin
        }
        graph_mark_unvisited(G, v);
        return;
    }
    for (uint32_t w = 0; w < graph_vertices(G); w += 1) { // For all edges
        if ((!graph_visited(G, w)) && (graph_has_edge(G, v, w))) { // Only edges and not visited
            path_push_vertex(c, w, G); // Push it onto the stack
            recursetimes += 1;
            dfs(G, w, c, s, outfile, cities); // test it recursively
            path_pop_vertex(c, &x, G); // Pop the stack after testing all of dfs
        }
    }
    graph_mark_unvisited(G, v);
}

int main(int argc, char *argv[]) {
    int choice;
    bool undir = false;
    bool sdout = false;
    char file[20];
    char fileout[100];
    verbose = false;
    while ((choice = getopt(argc, argv, "hvui:o:")) != -1) {
        switch (choice) {
        case 'h': fprintf(stderr, "%s", usage); break; // Print helps
        case 'v':
		 verbose = true;
		 break; // Verbose printing

        case 'u': undir = true; break;
        case 'i':
            if (optarg != NULL) {
                snprintf(file, 20, "%s", optarg);
            } else {
                fprintf(stderr, "%s", usage);
            }
            break;

        case 'o':
            if (optarg != NULL) {
                snprintf(file, 20, "%s", optarg);
                sdout = true;
            } else {
                fprintf(stderr, "%s", usage);
            }
            break;
        case '?': fprintf(stderr, "%s", usage); break;
        }
    }
    char buffer[1024];
    char *token;
    uint32_t temp[] = { 0, 0, 0 };
    FILE *stdin = fopen(file, "r");
    fgets(buffer, 1023, stdin);
    uint32_t amcities = atoi(buffer);

    Graph *G = graph_create(amcities, undir);
    char *cities[amcities - 1];
    for (uint32_t i = 0; fgets(buffer, 1023, stdin); i++) {
        buffer[strcspn(buffer, "\n")] = 0;
        if ((i) < amcities) {
            cities[i] = strndup(buffer, 1023);
        }
        if (i < amcities) {
            continue;
        }
        token = strtok(buffer, " ");
        for (int j = 0; token != NULL && j < 3; j++) {
            temp[j] = (uint32_t) strtoul(token, NULL, 10);
            token = strtok(NULL, " ");
        }
        graph_add_edge(G, temp[0], temp[1], temp[2]);
    }

    fclose(stdin);

    Path *c = path_create(); // For current path
    Path *s = path_create(); // For Previous Path

    path_push_vertex(c, 0, G);


    if (sdout == true) { //If user wants to print to file
        FILE *outfile = fopen(fileout, "w");
        dfs(G, 0, c, s, outfile, cities);
        fprintf(outfile, "Path Length: %u\n Path:", path_length(s));
        path_print(s, outfile, cities);
        fprintf(outfile, "Total recursive calls: %d\n", recursetimes);
        fclose(outfile);
    } else {
        dfs(G, 0, c, s, stdout, cities);
        fprintf(stdout, "Path Length: %u\n", path_length(s));
        path_print(s, stdout, cities);
        fprintf(stdout, "Total recursive calls: %d\n", recursetimes);
    }

    path_delete(&c);
    path_delete(&s);
    graph_delete(&G);
}

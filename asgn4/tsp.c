// Derick Pan
// dpan7
// Asgn4
#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <ctype.h>
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

char deadend[100] = "There's nowhere to go.\n";

int recursetimes = 0; //Counter for amoount of recursive calls
int flagham; //Flag that signals if all points are visited
bool verbose = false; //Verbose printing on or off?

void dfs(Graph *G, uint32_t v, Path *c, Path *s, FILE *outfile, char *cities[]) {

    graph_mark_visited(G, v);

    //Set flag to 0. For loop checks if all points have been visited.
    flagham = 0;
    for (uint32_t q = 0; q < graph_vertices(G); q++) {
        if (!graph_visited(G, q)) {
            flagham = 1; // If flagham ==1 then SOME POINT is not visited
            break;
        }
    }

    uint32_t x = 0; //Disregarded pointer

    //Base cases in this for loop
    if (flagham == 0) { //If all vertices have been visited

        if (path_vertices(s) == 0
            && graph_has_edge(G, v, 0)) { // if it's the first time for the shortest path.
            path_push_vertex(c, START_VERTEX, G); //Push in the return to origin
            path_copy(s, c);
            path_pop_vertex(c, &x, G); //Pop the return to origin
        }

        if (graph_has_edge(G, v, 0)) { //Check if the graph has an edge
            path_push_vertex(c, START_VERTEX, G); //Push in the starting vertex

            if (path_length(c)
                < path_length(s)) { //If Current path is shorter than shortest path in history
                path_copy(s, c); //Copy the path

                if (verbose == true) { //For verbose printing
                    fprintf(outfile, "Path Length: %u\n", path_length(s));
                    path_print(s, outfile, cities);
                }
            }
            path_pop_vertex(c, &x,
                G); //Pop the starting vertex off the top because we don't want repeats in the stack.
        }
        graph_mark_unvisited(G, v);
        return;
    }

    //Loops to test all the vertices.
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
    bool undir = false; //Flag to know if the graph is directed or undirected
    bool sdout = false; //Flag to know if the user wants to print into a file
    char file[20]; //Read the file input from user
    char fileout[100]; //File output for user
    verbose = false;
    while ((choice = getopt(argc, argv, "hvui:o:")) != -1) {
        switch (choice) {
        case 'h': fprintf(stderr, "%s", usage); break; // Print helps
        case 'v': verbose = true; break; // Verbose printing

        case 'u': undir = true; break;
        case 'i':

            if (optarg != NULL) { //If argument isn't null
                snprintf(file, 20, "%s", optarg);
                if (access(file, R_OK) != 0) { // if file exists
                    fprintf(stderr, "Error: failed to open infile.\n");
		    return 0;
                }
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
    char buffer[100]; //A buffer to store the lines in the file
    char *token; //token holds the i,j,k values but seperately with no whitespace
    uint32_t temp[] = { 0, 0, 0 }; //temporary array to store the i,j,k inputs
    FILE *stdin = fopen(file, "r"); //Open the file for reading
    fgets(buffer, 100, stdin); //Read the first line which is amount of vertices
    uint32_t amcities = atoi(buffer); //Set amcities (amount of cities) to above.
    if (amcities == 0) {
        fprintf(stderr, "%s", deadend);
        return 0;
    }
    Graph *G = graph_create(amcities, undir); //Create the graph
    char *cities[amcities - 1]; //The cities array

    for (uint32_t i = 0; fgets(buffer, 100, stdin); i++) {
        buffer[strcspn(buffer, "\n")] = 0; //Split up each line to whitespace

        if ((i) < amcities) { //If statement ONLY for cities
            if (strndup(buffer, 100) == NULL) {
                graph_delete(&G);
                fprintf(stderr, "%s", deadend);
                return 0;
            }
            cities[i] = strndup(buffer, 1023);
            continue;
        }

        token = strtok(buffer, " "); //Split the edges with respect to whitespace
        for (int j = 0; j < 3; j++) { //Add all of the items into temporary array.
            if (token != NULL) {
                temp[j] = (uint32_t) strtoul(token, NULL, 10);
                token = strtok(NULL, " ");
            } else {
                graph_delete(&G);
                fprintf(stderr, "Error: malformed edge.\n");
                return 0;
            }
        }
       	//Pass the temporary array of values to create an edge on graph
        graph_add_edge(G, temp[0], temp[1], temp[2]);
    }
    if (graph_vertices(G) == 1) {
        graph_delete(&G);
        fprintf(stderr, "%s", deadend);
        return 0;
    }
    fclose(stdin);

    Path *c = path_create(); // For current path
    Path *s = path_create(); // For Previous Path

    path_push_vertex(c, 0, G); //Push the first vertex so we have a starting point.

    if (sdout == true) { //If user wants to print to file
        FILE *outfile = fopen(fileout, "w");
        dfs(G, 0, c, s, outfile, cities);
        fprintf(outfile, "Path Length: %u\n Path:", path_length(s));
        path_print(s, outfile, cities);
        fprintf(outfile, "Total recursive calls: %d\n", recursetimes);
        fclose(outfile);

    } else { //If user doesn't want to print into a file
        dfs(G, 0, c, s, stdout, cities);
        fprintf(stdout, "Path Length: %u\n", path_length(s));
        path_print(s, stdout, cities);
        fprintf(stdout, "Total recursive calls: %d\n", recursetimes);
    }

    path_delete(&c);
    path_delete(&s);
    graph_delete(&G);
}

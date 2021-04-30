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

int64_t recuse = 0;
int flagham;
void dfs(Graph *G, uint32_t v, Path *c, Path *s, FILE *outfile, char *cities[]) {
    printf("rec %ld\n", recuse);
    recuse += 1;
    flagham = 0;

    graph_mark_visited(G, v);

    for (uint32_t q = 0; q < graph_vertices(G); q++) {
        if (!graph_visited(G, q)) {
            flagham = 1; // If flagham ==1 then SOME POINT is not visited
            break;
        }
    }
    //Hamiltonian = Go through all the points NO MORE THAN ONCE.
    /* Off by a few digits because I did not factor in the Last weight (OG Vertex)*/
    if (flagham == 0) {
        if (path_vertices(s) == 0 && graph_has_edge(G,v, 0)) { //This if statement seems fine
            fprintf(outfile,"I'm a solo\n");
            path_copy(s, c);
            path_print(s, outfile, cities);
        }

        if (graph_has_edge(G,v, 0)){
                path_copy(s, c);
                fprintf(outfile, "~");
                path_print(s, outfile, cities);
        }
        graph_mark_unvisited(G, v);
        return;
    }

    uint32_t x;
    for (uint32_t w = 0; w < graph_vertices(G); w += 1) { // For all edges
        if ((!graph_visited(G, w)) && (graph_has_edge(G,v, w))) { // Only edges and not visited
            path_push_vertex(c, w, G); // Push it onto the stack
            dfs(G, w, c, s, outfile, cities); // test it recursively
            path_pop_vertex(c, &x, G); // Pop the stack after testing all of dfs
        }
    }
    graph_mark_unvisited(G, v);
}

/*
Correct one:
        s->items[i] =2
s->items[i] =0
El-Cajon -> La-Mesa -> Jamul -> Campo -> La-Jolla -> Tijuana -> San-Ysidro ->
Santee -> Chula-Vista -> Lakeside -> El-Cajon

El-Cajon -> La-Mesa -> Chula-Vista -> Lakeside -> Jamul -> Campo -> La-Jolla -> Santee -> Tijuana -> San-Ysidro

El-Cajon
Santee
Lakeside
Chula-Vista
San-Ysidro
Campo
Jamul
La-Mesa
La-Jolla
Tijuana


El-Cajon -> Santee -> Chula-Vista -> Lakeside -> San-Ysidro -> Campo -> La-Jolla -> La-Mesa -> Jamul -> Tijuana
~El-Cajon -> Santee -> Chula-Vista -> Lakeside -> San-Ysidro -> La-Mesa -> Jamul -> Campo -> La-Jolla -> Tijuana
~El-Cajon -> Santee -> Chula-Vista -> Lakeside -> Jamul -> Campo -> La-Jolla -> La-Mesa -> San-Ysidro -> Tijuana
~El-Cajon -> San-Ysidro -> Tijuana -> Santee -> Jamul -> Campo -> La-Jolla -> La-Mesa -> Chula-Vista -> Lakeside
~El-Cajon -> La-Mesa -> Chula-Vista -> Lakeside -> Jamul -> Campo -> La-Jolla -> Santee -> Tijuana -> San-Ysidro

El-Cajon -> La-Mesa -> Chula-Vista -> Lakeside -> Jamul -> Campo -> La-Jolla -> Santee -> Tijuana -> San-Ysidro

*/
int main(int argc, char *argv[]) {
    int choice;
    bool undir = false;
    char file[20];
    char outf[50];
    while ((choice = getopt(argc, argv, "hv:ui:o:")) != -1) {
        switch (choice) {
        case 'h': fprintf(stderr, "%s", usage); break; // Print helps
        case 'v': break; // Verbose printing
        case 'u': undir = true; break;
        case 'i': snprintf(file, 20, "%s", optarg); break; // The file
        case 'o': snprintf(outf, 50, "%s", optarg); break;
        case '?': fprintf(stderr, "%s", usage); break;
        }
    }
    char buffer[1024];
    char *token;
    uint32_t temp[] = { 0, 0, 0 };
    FILE *read = fopen(file, "r");
    fgets(buffer, 1023, read);
    uint32_t amcities = atoi(buffer);

    Graph *G = graph_create(amcities, undir);
    char *cities[amcities - 1];
    for (uint32_t i = 0; fgets(buffer, 1023, read); i++) {
        buffer[strcspn(buffer, "\n")] = 0;
        if ((i) < amcities) {
            cities[i] = strndup(buffer, 1023);
        }
        if (i < amcities) {
            continue;
        }
        token = strtok(buffer, " ");
        for (int j = 0; token != NULL && j < 3; j++) {
            // printf("%s\n",token);
            temp[j] = (uint32_t) strtoul(token, NULL, 10);
            token = strtok(NULL, " ");
        }
        // printf("%u, %u, %u\n", temp[0], temp[1], temp[2]);
        graph_add_edge(G, temp[0], temp[1], temp[2]);
    }

    fclose(read);
    graph_print(G);

    Path *c = path_create(); // For current path
    Path *s = path_create(); // For Previous Path
    FILE *outfile = fopen("outfile.txt", "w");

    path_push_vertex(c, 0, G);

    dfs(G, 0, c, s, outfile, cities);
    printf("Path Length S: %u\n", path_length(s));
    printf("path Vertices S: %u\n", path_vertices(s));
    fprintf(outfile, "\n");
    path_print(s, outfile, cities);

    fclose(outfile);
    path_delete(&c);
    path_delete(&s);
    graph_delete(&G);
}

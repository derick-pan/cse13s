//Derick Pan
//dpan7
//Asgn4
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
int recuse = 0;

//uint32_t len = 100;
void dfs(Graph *G, uint32_t v, Path *c, Path *s) {
    recuse += 1;
    graph_mark_visited(G, v);
    //If is a hamiltonian path shorter than anything ever seen before
    //If current path is hamiltonian then path_copy
    //if (recuse >= 9000){fprintf(stderr, "recurse over 9k times\n");}
    if (path_vertices(c) == graph_vertices(G) && path_length(c) < path_length(s)) {
        path_copy(s, c);
        printf("Length: %u  recursive calls: %d  ", path_length(s), recuse);
        printf("vertices: %u\n", path_vertices(c));
    }

    //printf("%u ",path_vertices(c));
    //Current path is Hamiltoninan   AND current path is shorter than shortest path){
    //uint32_t x;
    for (uint32_t w = 0; w <= graph_vertices(G); w++) { //For all edges

        if (graph_has_edge(G, v, w) && !graph_visited(G, w)) { //Only edges and not visited
            path_push_vertex(c, w, G); //Push it onto the stack
            //path_push_vertex(s, w, G); //Push it onto the stack

            dfs(G, w, c, s); //test it recursively

            //path_pop_vertex(s, &x, G); //Push it onto the stack
            path_pop_vertex(c, &w, G); //Pop the stack after testing all of dfs
        } //If all visited then it stop
    }
    if (path_length(s) == 0) {
        //printf("%u ",path_vertices(c));
        path_copy(s, c);
    } /*
    if (path_length(c) < path_length(s)){
        printf("ayyy");
        path_copy(s, c);
    }*/
    graph_mark_unvisited(G, v);

    //printf("recursive calls: %d  \n", recuse);

    //graph_mark_unvisited(G, x);
    //printf("c->vertices, %u", path_vertices(c));
    //printf("Path Length S: %u\n Path Length C: %u \n",path_length(s),path_length(c));
}
////////###################################################################################/

int main(int argc, char *argv[]) {
    int choice;
    //bool flago= false;
    //bool undirectedflag= true;
    //char *cities[] = { "El-C", "santee", "lakeside", "chula", "san", "camp", "jam", "lames",
    //"lajol", "tijua" };
    char file[20];
    while ((choice = getopt(argc, argv, "hv:ui:o:")) != -1) {
        switch (choice) {
        case 'h': break; //Print helps
        case 'v': //Verbose printing
            break;
        case 'u': //undirectedflag = true; break;
        case 'i': snprintf(file, 20, "%s", optarg); break; //The file
        case 'o': break; //flago=true; break; //stdout
        }
    }
    char buffer[1024];
    char *token;

    uint32_t temp[] = { 0, 0, 0 };

    //printf("%s", file);

    FILE *read = fopen(file, "r");
    fgets(buffer, 1023, read);
    int amcities = atoi(buffer);
    Graph *G = graph_create(amcities, false);
    char *cities[amcities];

    for (int i = 0; fgets(buffer, 1023, read) != NULL; i++) {
        if ((i) < amcities) {
            //strcpy(cities[i],buffer);
            cities[i] = strndup(buffer, 1023);
            //printf("hi %s\n", cities[i]);
        }
        if (i < amcities) {
            continue;
        }
        token = strtok(buffer, " ");
        for (int j = 0; token != NULL && j < 3; j++) {
            //printf("%s\n",token);
            temp[j] = (uint32_t) strtoul(token, NULL, 10);
            token = strtok(NULL, " ");
        }
        //printf("%u, %u, %u\n", temp[0], temp[1], temp[2]);
        graph_add_edge(G, temp[0], temp[1], temp[2]);
    }
    fclose(read);
    graph_print(G);
    Path *c = path_create(); //For current path
    Path *s = path_create(); //For Previous Path
    FILE *outfile = fopen("outfile.txt", "w");
    dfs(G, 0, c, s);
    printf("Path Length: %u\n", path_length(s));
    printf("path Vertices: %u\n", path_vertices(s));
    path_print(s, outfile, cities);

    fclose(outfile);
    //free(cities);
    //
    //fclose(outfile);

    graph_delete(&G);
}

/*
int main() {
    Graph *G = graph_create(7, true);
    graph_add_edge(G, 0, 1, 10);
    graph_add_edge(G, 1, 2, 2);
    graph_add_edge(G, 1, 3, 5);
    graph_add_edge(G, 2, 5, 3);
    graph_add_edge(G, 2, 6, 5);
    graph_add_edge(G, 3, 4, 21);
    graph_print(G);
    printf("\n");

    path_push_vertex(p, 0, G);
    printf ("0Path Length: %u\n", path_length(p));  //0

	path_push_vertex(p, 1, G);
    printf ("1Path Length: %u\n", path_length(p)); //10

    #path_push_vertex(p, 2, G)
    printf ("2Path Length: %u\n", path_length(p)); //10
    printf ("Amount of vertices: %u\n", path_vertices(p)); //3

    Path *p = path_create();
    Path *s = path_create();
    dfs(G, 0, p, s);
    char *cities[] = { "El-C", "santee", "lakeside", "chula", "san", "camp", "jam", "lames",
        "lajol", "tijua" };
    FILE *outfile = fopen("outfile.txt", "w");
    path_print(s, outfile, cities);
    path_delete(&p);
    path_delete(&s);
    graph_delete(&G);
}
*/

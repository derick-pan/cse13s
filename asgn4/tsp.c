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
int flagham;

void dfs(Graph *G, uint32_t v, Path *c, Path *s) {
    recuse += 1;

    graph_mark_visited(G, v);
    //printf("got into dfs here\n");
//   Hamiltonian if your path goes through all the points and gets back
//   to beginning, that is Hamiltonian
//Shortest hamiltonian is the shortest one that does so
    if (v==0 && path_vertices(c)){ //If this is my first vertex, add 1 to vertex
        printf("ONCE \n");
        path_push_vertex(c, START_VERTEX,G);
        path_copy(s, c);
    }
    /* Loop to test if ALL have been visited */
    flagham =0;
    for (uint32_t q = 0; q < graph_vertices(G); q++){
        if (!graph_visited(G,q)){
            flagham = 1; //If flagham ==1 then something wasn't visited
            break;
        }
    }

 /* if   All visted &&        all vertices but current   */
    if (flagham ==0 && path_vertices(c) == graph_vertices(G)-1){
        printf("+1 hamiltonian Path\n");
        if (path_length(s)==0){
            printf("am i ever here??, Recursion # : %u \n", recuse);
            path_push_vertex(c, v,G); //Add in the final point
            path_copy(s, c);
            return;
        }
        /* If this is currently the shortest path then... */
        else if (path_length(c) < path_length(s)) {
            path_push_vertex(c, v,G); //Add in the final point
            path_copy(s, c);  //A Hamiltonian path
            printf("what am i to you \n");
            return;
            }
        else{return;}
    }

    uint32_t x;
    for (uint32_t w = 0; w < graph_vertices(G); w++) { //For all edges
        if (graph_has_edge(G, v, w) && !graph_visited(G, w)) { //Only edges and not visited
            flagham = 1;
            path_push_vertex(c, w, G);  //Push it onto the stack
            dfs(G, w, c, s);            //test it recursively
            path_pop_vertex(c, &x, G);  //Pop the stack after testing all of dfs
        }
    }
    graph_mark_unvisited(G, v);
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
    //path_push_vertex(c, START_VERTEX,G);
    dfs(G, 0, c, s);
    printf("Path Length S: %u\n", path_length(s));
    printf("path Vertices S: %u\n", path_vertices(s));
    //printf("Path Length C: %u\n", path_length(c));
    //printf("path Vertices C: %u\n", path_vertices(c));
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

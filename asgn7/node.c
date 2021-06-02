// Derick Pan
// dpan7
// node.c
#include "node.h"

#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Node Node;

// Constructor function for Node
Node *node_create(char *oldspeak, char *newspeak) {
    //Allocate memory and copy character of oldspeak
    //Allocate memory and copy character of newspeak
    Node *n = (Node *) malloc(sizeof(Node));
    if (oldspeak != NULL) {
        n->oldspeak = strdup(oldspeak);
    } else {
        n->oldspeak = NULL;
    }
    if (newspeak != NULL) {
        n->newspeak = strdup(newspeak);
    } else {
        n->newspeak = NULL;
    }
    n->next = NULL;
    n->prev = NULL;
    return n;
}

//Destructor Function for Node
void node_delete(Node **n) {
    free((*n)->oldspeak);
    free((*n)->newspeak);
    free(*n);
    *n = NULL;
}

//Following printf statements are from Asgn7 doc
void node_print(Node *n) {
    //If node contains both old and newspeak then print
    if (n->oldspeak && n->newspeak) {
        printf("%s -> %s\n", n->oldspeak, n->newspeak);
        //Else just print oldspeak
    } else if (n->oldspeak) { //Just print oldspeak
        printf("%s\n", n->oldspeak);
    }
}

//Derick Pan
//dpan7
//node.c
//
#include "node.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
typedef struct Node Node;
//Set node's symbol as symbol, frequency as frequency
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

//Join left and child node, and return parent
Node *node_join(Node *left, Node *right) {
    //uint8_t name = (uint8_t) strtoul("$",NULL,10);
    //uint64_t freq = ;
    //printf( "Frequency: %" PRIu64 "\n"  ,freq);
    Node *parentn = node_create(111, left->frequency + right->frequency);
    parentn->left = left;
    parentn->right = right;
    return parentn;
}

void node_print(Node *n) {
    if (n) {
        printf("symbol: %u | ", n->symbol);
        printf("my freq: %" PRIu64 "\n", n->frequency);
        printf("I'm created! \n");
    } else {
        printf("i'm not created\n");
    }
}

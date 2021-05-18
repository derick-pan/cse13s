//Derick Pan
//dpan7
//node.c
#include "node.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
typedef struct Node Node;

// Constructor function for a node
Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->symbol = symbol;
    n->frequency = frequency;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// Destructor function for a node
void node_delete(Node **n) {
    free(*n);
    *n = NULL;
}

//Join left and child node, and return parent
Node *node_join(Node *left, Node *right) {
    uint8_t dollasign = 36;
    Node *parent = node_create(dollasign, (left->frequency + right->frequency));
    parent->left = left;
    parent->right = right;
    return parent;
}

//Debug function to print node
void node_print(Node *n) {
    if (n) {
        printf("symbol: %c | ", n->symbol);
        printf("my freq: %" PRIu64 "\n", n->frequency);

    } else {
        printf("i'm not created\n");
    }
}

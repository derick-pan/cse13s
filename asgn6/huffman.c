//Derick Pan
//dpan7
//huffman.c
#include "huffman.h"

#include "code.h"
#include "defines.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*  ALPHABET = 256
    BLOCK = 4096   */

Node *build_tree(uint64_t hist[static ALPHABET]) {
    Node *temp;
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            temp = node_create((uint8_t) i, hist[i]);
            enqueue(q, temp);
        }
    }
    Node *l;
    Node *r;
    Node *j;
    while (pq_size(q) >= 2) {
        dequeue(q, &l); // dequeue the left node
        dequeue(q, &r); // dequeue the right node
        j = node_join(l, r); // Join the Nodes together and enqueue it
        enqueue(q, j);
    }

    dequeue(q, &j); // dequeue the Root Node
    pq_delete(&q); // Delete the Queue
    return j; // Return the Root Node
}

void build_codes(Node *root, Code table[static ALPHABET]) {

    //If node is a Leaf Node: then save it
    if (NULL == root->left && NULL == root->right) {
        table[root->symbol] = *table;
        return;
    }
    //Else root is an Interior Node
    uint8_t temp; // Holder for the popped bits
    Code *c = table; // Current code

    code_push_bit(c, 0); // Push a 0 because we're going left
    build_codes(root->left, c); // RECURSE to left link
    code_pop_bit(c, &temp); // Pop from c

    code_push_bit(c, 1); // Push a 1 because we're going right
    build_codes(root->right, c); // RECURSE to right link
    code_pop_bit(c, &temp); // pop from c
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Stack *s = stack_create(nbytes); // Stack to reconstruct tree
    // Iterate over contents of the tree dump
    for (uint16_t i = 0; i < nbytes; i += 1) {
        //If element is an L then we create a node
        if (tree[i] == 'L') {
            // We create & push a node where the frequency doesn't matter
            Node *n = node_create(tree[i + 1], 1);
            stack_push(s, n);
            i += 1;
        } // otherwise element is an interior node so we create a parent node.
        else if (tree[i] == 'I') {
            Node *r;
            stack_pop(s, &r); // Right Child
            Node *l;
            stack_pop(s, &l); // Left Child
            Node *d = node_join(l, r); // Parent
            stack_push(s, d);
        }
    }
    Node *root;
    stack_pop(s, &root); //We Pop the Parent Node and return it
    stack_delete(&s);
    return root;
}

void delete_tree(Node **root) {

    //If I am interior node, recurse left and right then delete the node
    if ((*root)->left != NULL && (*root)->right != NULL) {
        delete_tree(&(*root)->left); // RECURSE to left link
        delete_tree(&(*root)->right); // RECURSE to right link
        node_delete(root);

    } else { //If i'm a leaf then delete node
        node_delete(root);
        return;
    }
}

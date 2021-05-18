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

#define ALPHABET 256

Node *build_tree(uint64_t hist[static ALPHABET]) {
    //uint32_t freq;
    Node *temp;
    PriorityQueue *q = pq_create(ALPHABET);
    for (uint32_t i = 0; i < ALPHABET; i++) {
        if (hist[i] > 0) {
            printf("index here: %u Frequency here: %" PRIu64 "\n", i, hist[i]);
            temp = node_create(i, hist[i]);
            enqueue(q, temp);
        }
    }
    //printf("QUEUEUEUEUEUEUE\n\n");
    //pq_print(q);
    //printf("\n\nQUEUEUEUEUEUEUE\n");
    //node_delete(&temp); //This node is no longer needed
    Node *l;
    Node *r;
    Node *j;
    while (pq_size(q) >= 2) {
        dequeue(q, &l);
        dequeue(q, &r);
        //printf("Dq L sym: %u, R: %u ", l->symbol,  r->symbol);

        j = node_join(l, r);
        //printf("Dq L sym: %u, R: %u ", l->symbol,  r->symbol);
        enqueue(q, j);
        //printf("QUEUEUEUEUEUEUE\n\n");
        //pq_print(q);
        //printf("\n\nQUEUEUEUEUEUEUE\n");
    }
    dequeue(q, &j);
    printf("printing the queuee\n");
    pq_print(q);
    pq_delete(&q);

    return j;
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    //While i'm an interior node

    if (root->left == NULL && root->left == NULL) {
        table[root->symbol] = *table;

        printf("symbol: %c\n", root->symbol);

        code_print(&table[root->symbol]);

        return;
    } //Must be an interior node

    uint8_t temp;
    Code *c = table; //Current code
    code_push_bit(c, 0); // Push a 0 because we're going left
    build_codes(root->left, c); // RECURSE to left link
    code_pop_bit(c, &temp);

    //Push, recurse right, pop
    code_push_bit(c, 1);
    build_codes(root->right, c); // RECURSE to right
    code_pop_bit(c, &temp); // pop from c
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {

    Stack *s = stack_create(nbytes);
    //uint8_t treedump = *tree;

    for (uint8_t i = 0; i < nbytes; i += 1) {
        //printf("Tree: %c \n", tree[i]);
        if (tree[i] == 'L') {
            printf("Push Leaf\n");
            Node *n = node_create(tree[i + 1], 3); //What's the frequency
            stack_push(s, n);
            stack_print(s);
            //i+=1;
        } else if (tree[i] == 'I') {
            printf("Push I\n");

            Node *r;
            stack_pop(s, &r); //Right Child
            Node *l;
            stack_pop(s, &l); //Left Child
            Node *d = node_join(l, r);
            stack_push(s, d);
            stack_print(s);
            //stack_print(s);
        }
    }
    stack_print(s);
    Node *root;
    stack_pop(s, &root);
    stack_delete(&s);
    return root;
}

void delete_tree(Node **root) {

    //printf("Deleting the tree\n");

    if ((*root)->left == NULL && (*root)->right == NULL) {

        node_delete(root);

        return;
    } else { //Must be an interior node
        delete_tree(&(*root)->left); // RECURSE to left link
        delete_tree(&(*root)->right); // RECURSE to right
        node_delete(root);
    }
}

//Derick Pan
//dpan7
//huffman.c
//#include "huffman.h"
#include "huffman.h"

#include "code.h"
#include "defines.h"
#include "node.h"
#include "pq.h"

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
            //printf("index here: %u Frequency here: %" PRIu64 "\n", i, hist[i]);
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
    //node_delete(&l), node_delete(&r);
    // The one node left in priority queue is the root node
    dequeue(q, &j);
    //pq_delete(&q);
    return j;
}

void build_codes(Node *root, Code table[static ALPHABET]) {

    uint8_t temp = 0;
    //While i'm an interior node
    //If Current node is a leaf then save the code it took to get here
    if (root->left == NULL && root->left == NULL) {
        //If there's a left kid then there's a right, same vice versa
        //Save this code into code table.
        //Already in the code no?

        //printf("Ascii and index: %u\n", root->symbol);
        //code_print(&c);

        table[root->symbol] = *table;
        //code_print(&table[root->symbol]);

        return;
    } else { //Must be an interior node
        Code *c = table; //Current code
        code_push_bit(c, 0); // Push a 0 because we're going left
        build_codes(root->left, c); // RECURSE to left link
        code_pop_bit(c, &temp);

        //Push, recurse right, pop
        code_push_bit(c, 1);
        build_codes(root->right, c); // RECURSE to right
        code_pop_bit(c, &temp); // pop from c

    }
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]);

void delete_tree(Node **root);

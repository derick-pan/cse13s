//Derick Pan
//dpan7
//huffman.c
//#include "huffman.h"
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

// ALPHABET      256

Node *build_tree(uint64_t hist[ALPHABET]){
    uint32_t freq;
    Node *temp;
    PriorityQueue *q = pq_create(5);
    for (uint32_t i = 0; i < ALPHABET; i++){
        freq = hist[i / 64] >> (i % 64) & 0x1; //Gets the bit
        if (freq >0){
            temp = node_create(i, freq);
            enqueue(q,temp);
        }
    }
    node_delete(&temp); //This node is no longer needed
    Node *l;
    Node *r;
    Node *j;
    while (pq_size(q)>= 2){
        dequeue(q, &l);
        dequeue(q, &r);
        j = node_join(l, r);
        enqueue(q, j);
    }
    node_delete(&l), node_delete(&r);
    // The one node left in priority queue is the root node
    dequeue(q,&j);
    pq_delete(&q);
    return j;
}

void build_codes(Node *root, Code table[static ALPHABET])

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]);

void delete_tree(Node **root);

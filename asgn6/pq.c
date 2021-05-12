//Derick Pan
//dpan7
//pq.c
#include "pq.h"

#include "node.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
static inline uint8_t prev_pos(uint32_t tail, uint32_t cap) { //from lab1 documentation
    return ((tail + cap - 1) % cap);
}

static inline uint8_t next_pos(uint32_t tail, uint32_t cap) { //from lab1 documentation
    return ((tail + 1) % cap);
}*/
typedef struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    uint32_t head;
    uint32_t tail;
    Node **items; //Pointer to the first element of array
} PriorityQueue;

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
        q->size = 0;
        q->head = 0;
        q->tail = 0;
        //printf("here");
        q->items = (Node **) calloc(capacity, sizeof(Node *)); //allocating array of node poitners
        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void pq_delete(PriorityQueue **q) {
    free((*q)->items);
    free(*q);
    *q = NULL;
}

bool pq_empty(PriorityQueue *q) {
    if (q->size == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->size;
}

//My enqueue follows similar implementation from my Asgn3 shell.c
//the lower frequencies should stay towards the head (High priority)
// [lower, to , higher]
// Min priority Queue

//Mimick an Insertion sort when enqueuing a node, finding
//a correct position for the node and shifting everything back

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }
    // Begin searching for correct position to place node n
    uint64_t curr = n->frequency; //The value we need to insert
    int position = q->tail - 1; // Store the position to test
    //This felt more like a bubble sort
    //While the testing position is >= 0 and
    //the Node's frequency is less than the position being tested.
    while (position >= 0 && (curr < ((q->items[position])->frequency))) {
        //We move the node up a spot if so.
        q->items[position + 1] = q->items[position];
        position -= 1;
    }
    q->items[position + 1] = n;
    q->size += 1;
    q->tail += 1;

    return true;
}

//dequeue node with highest Priority || lowest frequencies
//Pass back the dequeued through the double pointer
bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }
    *n = q->items[q->head];
    q->tail -= 1;
    q->size -= 1;
    *n = q->items[0];
    //Shift the elements one back
    for (uint32_t i = 0; i < q->size; i++) {
        q->items[i] = q->items[i + 1];
    }
    return true;
}

void pq_print(PriorityQueue *q) {

    for (uint32_t i = 0; i < q->size; i++) {
        //printf("%u\n\n", i);
        printf("postion %u  |  symbol: %u\n", i, q->items[i]->symbol);
    }
}

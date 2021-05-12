//Derick Pan
//dpan7
//pq.c
#include "pq.h"
#include "node.h"
#include <inttypes.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static inline uint8_t prev_pos(uint32_t tail, uint32_t cap) { //from lab1 documentation
    return ((tail + cap - 1) % cap);
}

static inline uint8_t next_pos(uint32_t tail, uint32_t cap) { //from lab1 documentation
    return ((tail + 1) % cap);
}
typedef struct PriorityQueue {
    uint32_t capacity;
    uint32_t size;
    uint32_t head;
    uint32_t tail;
    Node **items; //Pointer to the first element of array
} PriorityQueue;

PriorityQueue *pq_create(uint32_t capacity){
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
        q->size = 0;
        q->head = 0;
        q->tail = 0;
        q->items = (Node **) calloc(capacity, sizeof(Node*)); //allocating array of node poitners


        if (!q->items) {
            free(q);
            q = NULL;
        }
    }
    return q;
}

void pq_delete(PriorityQueue **q){
    free((*q)->items);
    free(*q);
    *q = NULL;
}

bool pq_empty(PriorityQueue *q){
    if (q->size == 0 ){
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q){
    if (q->size == q->capacity) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q){
    return q->size;
}

//My enqueue follows similar implementation from my Asgn3 shell.c
//the lower frequencies should stay towards the head (High priority)
// [lower, to , higher]
// Min priority Queue

//Mimick an Insertion sort when enqueuing a node, finding
//a correct position for the node and shifting everything back

bool enqueue(PriorityQueue *q, Node *n){
    if(pq_full(q)){
        return false;
    }
    // Begin searching for correct position to place node n
    uint32_t curr = n->frequency;    //The value we need to insert
    int position = prev_pos(q->tail, q->capacity); //Store my position

    //Position has a value in the array
    //While my frequency is less than position before me && it exists
    while (curr < (q->items[position])->frequency && !pq_empty(q)) {
        //Then current position is now the position before me
        q->items[next_pos(position,q->capacity)] = q->items[position];
        position = prev_pos(position, q->capacity);
    }
    q->items[next_pos(position,q->capacity)] = n;
    q->size +=1;
    q->tail = next_pos(q->tail,q->capacity);
return true;
}

//dequeue node with highest Priority || lowest frequencies

bool dequeue(PriorityQueue *q, Node **n){
    if (pq_empty(q)) {
        return false;
    }
    q->head = next_pos(q->head, q->capacity);
    *n = q->items[q->head];
    q->size -=1;
    return true;
}


void pq_print(PriorityQueue *q);

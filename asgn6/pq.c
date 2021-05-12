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

PriorityQueue *pq_create(uint32_t capacity){
    PriorityQueue *q = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (q) {
        q->capacity = capacity;
        q->size = 0;
        q->head = 0;
        q->tail = 0;
        //printf("here");
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
    uint64_t curr = n->frequency;    //The value we need to insert
    //printf("here1\n");
    int position = prev_pos(q->tail, q->capacity); //Store my position
    //printf("After storing position\n");
    //Position has a value in the array
    //While my frequency is less than position before me && it exists
    //printf("%u is the q->items[0]->frequency\n",(q->items[0])->frequency))
    //printf("position is: %u \n", position);

    //This will be a linear queue
    while (position >= 0 && (curr < ((q->items[position])->frequency))) {

        //Then current position is now the position before me
        q->items[position +1] = q->items[position];
        //printf("Crashed here\n");
        position = prev_pos(position, q->capacity);
        //printf("Crashed here??? %u\n\n", position);
    }
    printf("Where the f are you crashing\n");
    //pq_print(q);
    printf("\nThe location of the crash is here   %u \n",next_pos(position,q->capacity));
    q->items[q->tail] = n;
    //printf("The index of what i Enqueued is %u\n",next_pos(position,q->capacity));
    printf("pos and tail difference is as follows:\n\n %u , %u\n\n",next_pos(position,q->capacity),next_pos(q->tail,q->capacity) );

    q->size +=1;
    q->tail = next_pos(q->tail,q->capacity);
    printf("Symbol of what I just added in  \n" );
    node_print(q->items[next_pos(position,q->capacity)]);
    //node_print(q->items[next_pos(position,q->capacity)]);
    printf("\n\n\n");
return true;
}

//dequeue node with highest Priority || lowest frequencies
bool dequeue(PriorityQueue *q, Node **n){
    if (pq_empty(q)) {
        return false;
    }
    //q->head = next_pos(q->head, q->capacity);
    q->size -=1;
    *n = q->items[0];
    //Shift the elements one back
    for (uint32_t i = 0; i < q->size ; i++){
        q->items[i] = q->items[i+1];

    }
    *n = q->items[q->head];

    return true;
}


void pq_print(PriorityQueue *q){

    for (uint32_t i = 0 ; i < q->capacity; i++){
        printf("%u\n\n", i);
        printf("postion %u  |  symbol: %u", i, q->items[i]->symbol);



    }

}

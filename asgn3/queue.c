//Derick Pan
//dpan7
//Asgn3 2021
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <stdint.h>

typedef struct Queue {
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	uint32_t capacity;
	int64_t *items;
}Queue;

Queue *queue_create(uint32_t capacity) {
	Queue *q = (Queue *) malloc(sizeof(Queue));
	if (q) {
		q->head = q->tail = 0;
		q->capacity = capacity;
		q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
		if (!q->items) {
			free(q);
		}
	}
	return q;
}
void queue_delete(Queue **q) {
	if (*q && (*q)->items) {
		free((*q)->items);
		free(*q);
		*q = NULL;
	}
	return;
}

bool queue_empty(Queue *q) {
	if (q->head == q->tail){
		return true;
	}
	return false;
	
}
bool queue_full(Queue *q) {
	if (q->head +1 == q->tail) {
		return true;
	}
	return false;
}

uint32_t queue_size(Queue *q){
	return q->head;
}

bool enqueue(Queue *q, int64_t x) {
	if(queue_full(q)){
		return false;
	}
	
	q->items[q->tail]= x;
	q->tail   += 1;
	return true;
}

bool dequeue(Queue *q, int64_t *x) {
	if (queue_empty(q)){
		return false; }
	q->head += 1;
	*x = q->items[q->head]; 
	return true;
}
void queue_print(Queue *q) {
        for (uint32_t i=0; i<queue_size(q); i +=1){
                printf("%ld\n",q->items[i]);
        }
        printf("-------------------------------------------------\n");
        return;
}


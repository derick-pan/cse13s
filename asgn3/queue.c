//Derick Pan
//dpan7
//Asgn3 2021
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <stdint.h>

typedef struct Queue ;
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	uint32_t capacity;
}Queue;
Queue *queue_create(uint32_t capacity);

void queue_delete(Queue **q);

bool queue_empty(Queue *q);

bool queue_full(Queue *q);

uint32_t queue_size(Queue *q);

bool enqueue(Queue *q, int64_t x);

bool dequeue(Queue *q, int64_t *x);

void queue_print(Queue *q);


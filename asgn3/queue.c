//Derick Pan
//dpan7
//Asgn3 2021
#include "queue.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct Queue {
    uint32_t head;
    uint32_t tail;
    uint32_t size;
    uint32_t capacity;
    int64_t *items;
} Queue;

Queue *queue_create(uint32_t capacity) {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    if (q) {
        q->head = 0;
        q->size = 0;
        q->tail = 0;
        q->capacity = capacity;
        q->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!q->items) {
            free(q);
            q = NULL;
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
    if (q->size == 0) {
        return true;
    }
    return false;
}
bool queue_full(Queue *q) {
    //	printf("size \n%" PRIu32 "\ncapacity %" PRIu32, q->size, q->capacity );

    if (q->tail == q->head - 1 || (q->tail == q->capacity + 1 && q->head == 0)) {
        return true;
    }
    return false;
}

uint32_t queue_size(Queue *q) {
    return q->size;
}

bool enqueue(Queue *q, int64_t x) {
    if (queue_full(q)) {
        return false;
    }
    if (q->tail == q->capacity && q->head != 0) {
        q->tail = 0;
    }
    q->items[q->tail] = x;
    q->tail += 1; //next empty spot
    q->size += 1; //current size
    return true;
}

bool dequeue(Queue *q, int64_t *x) {
    if (queue_empty(q)) {
        return false;
    }
    if (q->head == q->capacity) {
        q->head = 0;
    }
    *x = q->items[q->head];
    q->head += 1; //will have an item
    q->size -= 1;
    return true;
}
void queue_print(Queue *q) {
    for (uint32_t i = 0; i < queue_size(q); i += 1) {
        printf("%ld\n", q->items[i]);
    }
    printf("-------------------------------------------------\n");
    return;
}

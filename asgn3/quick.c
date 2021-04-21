//Derick pan
//dpan7
//Asgn3
#include "quick.h"

#include "queue.h"
#include "stack.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int quickmoves =0;
int quickcompares=0;
//Gets immediate left and right value in array

int64_t partition(uint32_t *A, int64_t lo, int64_t hi) {
    int64_t temp;
    int64_t pivot = A[lo + ((hi - lo) / 2)]; //FIX
    int64_t i = lo - 1; //Gets the immediate to the left
    int64_t j = hi + 1; //Gets the immediate to the right
    while (i < j) {
	quickcompares +=1;
        i += 1;
        while (A[i] < pivot) {
		quickcompares +=1;
            i += 1;
        }
        j -= 1;
        while (A[j] > pivot) {
		quickcompares +=1;
            j -= 1;
        }
	quickcompares +=1;
        if (i < j) {
            quickmoves += 3;//Correct
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    return j;
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    int64_t low = 0;
    int64_t high = n - 1;
    int64_t p; //for partition
    int64_t x; //Pointer
    Stack *a = stack_create(n);
    stack_push(a, low);
    stack_push(a, high);
    while (!stack_empty(a)) {
	//quickcompares +=3;
        stack_pop(a, &x);
        high = x;
        stack_pop(a, &x);
        low = x;
        p = partition(A, low, high);
        if (low < p) {
            stack_push(a, low);
            stack_push(a, p);
        }
        if (high > p + 1) {
            stack_push(a, p + 1);
            stack_push(a, high);
        }
    }
    stack_delete(&a);
    printf(
        "Quick Sort (Stack)\n%d elements, %d moves, %d compares\n", n, quickmoves, quickcompares);
    quickmoves = 0;
    quickcompares =0;
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    int64_t low = 0;
    int64_t high = n - 1;
    int64_t p; //for partition
    int64_t x; //Pointer
    Queue *a = queue_create(n);
    enqueue(a, low);
    enqueue(a, high);
    while (!queue_empty(a)) {
	//quickcompares +=2;
        dequeue(a, &x);
        low = x;
        dequeue(a, &x);
        high = x;
        p = partition(A, low, high);
        if (low < p) {
            enqueue(a, low);
            enqueue(a, p);
        }
        if (high > p + 1) {
            enqueue(a, p + 1);
            enqueue(a, high);
        }
    }
    queue_delete(&a);
    printf(
        "Quick Sort (Queue)\n%d elements, %d moves, %d compares\n", n, quickmoves, quickcompares);
    quickmoves = 0;
    quickcompares =0;
}

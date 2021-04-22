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
int quickmoves;
int quickcompares;
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
            quickmoves += 3;
	    
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    return j;
}

void quick_sort_stack(uint32_t *A, uint32_t n) {
    uint32_t size=2; 
    uint32_t maxsize =0;
    quickmoves = 0;
    quickcompares =0;
    int64_t low = 0;
    int64_t high = n - 1;
    int64_t p; //for partition
    int64_t x; //Pointer
    Stack *a = stack_create(n);
    stack_push(a, low);
    stack_push(a, high);
    while (!stack_empty(a)) {
	if ((stack_size(a) >= (size)) && (stack_size(a) >= maxsize)){
		maxsize = stack_size(a);
	}	
        stack_pop(a, &x);
        high = x;
        stack_pop(a, &x);
        low = x;
        p = partition(A, low, high);
	size -=2;
        if (low < p) {
            stack_push(a, low);
            stack_push(a, p);
	    size +=2;
        }
        if (high > p + 1) {
            stack_push(a, p + 1);
            stack_push(a, high);
	    size +=2;
        }
    }
    stack_delete(&a);
    printf(
        "Quick Sort (Stack)\n%d elements, %d moves, %d compares\nMax stack size: %u\n", n, quickmoves, quickcompares,maxsize);
}

void quick_sort_queue(uint32_t *A, uint32_t n) {
    uint32_t size=2; 
    uint32_t maxsize =0;
    quickmoves = 0;
    quickcompares =0;
    int64_t low = 0;
    int64_t high = n - 1;
    int64_t p; //for partition
    int64_t x; //Pointer
    Queue *a = queue_create(n);
    enqueue(a, low);
    enqueue(a, high);
    while (!queue_empty(a)) {
	if ((queue_size(a) >= (size)) && (queue_size(a) >= maxsize)){
		maxsize = queue_size(a);
	}	
        dequeue(a, &x);
        low = x;
        dequeue(a, &x);
        high = x;
	size -=2;
        p = partition(A, low, high);
        if (low < p) {
            enqueue(a, low);
            enqueue(a, p);
	    size +=2;
        }
        if (high > p + 1) {
            enqueue(a, p + 1);
            enqueue(a, high);
	    size +=2;
        }
    }
    queue_delete(&a);
    printf(
        "Quick Sort (Queue)\n%d elements, %d moves, %d compares\nMax queue size: %u\n", n, quickmoves, quickcompares,maxsize);
}

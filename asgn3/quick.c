//Derick pan
//dpan7
//Asgn3
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "quick.h"


//Gets immediate left and right value in array
int64_t partition(uint32_t *A , int64_t lo , int64_t hi ) {
	int64_t temp; 
	int64_t pivot = A[lo+ floor((hi-lo) /2)];//FIX 
	int64_t i = lo -1;//Gets the immediate to the left
	int64_t j = hi +1;//Gets the immediate to the right

	while (i < j) {
		i += 1;
		while (A[i] < pivot) {
			i+=1;
		}
		j -=1;
		while (A[j] > pivot) {
			j -= 1;
		}
		if (i< j) {
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	return j;
}		

void quick_sort_stack(uint32_t *A, uint32_t n) {
	int low =0;
	int high = n -1;

	uint32_t stack = Stack *stack_create(capacity);
	stack[0] = lo;
	stack_push(stack, 
	stack[1] = hi;
	int len == 2;
	while(len != 0) {
		high = stack[n];
		low = stack[n-1];
		len = len-2
		p = partition(A,low,high);
		if (low < p) {
			//stack.append(lo)
			//stack.append(p)
		}
		if (hi > p+1) {
			//stack.append(p+1)
			//stack.append(hi)
		}


	}	









}


void quick_sort_queue(uint32_t *A, uint32_t n);

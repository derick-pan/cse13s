//Derick pan
//dpan7
//Asgn3
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "quick.h"
#include "stack.h"
//Gets immediate left and right value in array
int64_t partition(uint32_t *A , int64_t lo , int64_t hi ) {
	int64_t temp; 
	int64_t pivot = A[lo+ ((hi-lo) /2)];//FIX 
	int64_t i = lo -1;//Gets the immediate to the left
	int64_t j = hi +1;//Gets the immediate to the right

	while (i < j) {
		i += 1;
		do{ i+=1;
	   		} while (A[i] < pivot);
		
		j -=1;
		do { j-=1;
			} while (A[j] > pivot);
		if (i< j) {
			temp = A[i];
			A[i] = A[j];
			A[j] = temp;
		}
	}
	return j;
}		

void quick_sort_stack(uint32_t *A, uint32_t n) {
	int64_t low =0;
	int64_t high = n -1;
	int64_t p; //for partition
	int64_t x; //Pointer
	Stack *a = stack_create(n);
	stack_push(a, low);
	stack_push(a, high);
	while(!stack_empty(a)) {
		high= stack_pop(a,&x);
		low = stack_pop(a,&x);
		p = partition(A,low,high);
		if (low < p) {
			stack_push(a,low);
			stack_push(a,p);
		}
		if (high > p+1) {
			stack_push(a,p+1);
			stack_push(a,high);
		}
		stack_print(a);
		break;

	}	
}


void quick_sort_queue(uint32_t *A, uint32_t n);

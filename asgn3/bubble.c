//Derick Pan
//dpan7
//Asgn3 2021 
#include <stdio.h>
#include <stdlib.h>
#include "bubble.h"
#include <stdint.h>
#include <stdint.h>
		//Pointer      //Size
void bubble_sort(uint32_t *A, uint32_t n) {
	int swapped = 1;
	while (swapped) {
		swapped = 0;
		for( uint32_t i =1; i < n; i +=1) {
			if ( A[i] < A[i-1] ) {

				int temp = A[i];
				A[i] = A[i-1];
				A[i-1] = temp;
				swapped = 1;
			}
		}
		n -= 1;
	}
}
				




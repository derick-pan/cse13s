//Derick Pan
//dpan7
//Asgn3 2021 
#include <stdio.h>
#include <stdlib.h>
#include "bubble.h"
		//Pointer      //Size
void bubble_sort(unit32_t *A, unit32_t n) {
	int swapped = 1;
	while (swapped) {
		swapped = 0;
		for( int i =0; i <= n; i +=1) {
			if ( A < (A-1) ) {
				int temp = *A;
				*A = *(A-1);
				*(A-1) = temp;
				swapped = 1;
			}
		}
		n -= 1;
	}
}
				




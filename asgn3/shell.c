//Derick Pan
//dpan7
//Asgn3 2021
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "gaps.h"
#include <stdint.h>
void shell_sort(uint32_t *A, uint32_t n) {
	uint32_t temp;
	uint32_t curr;
	uint32_t gap;
	uint32_t GapLen = sizeof(gaps)/sizeof(int);

	for (uint32_t g = 0; g < GapLen; g+=1){  //gap represents the value
		//set gap to the value
		gap = gaps[g];

		for (uint32_t i = g ; i<=n ; i+=1) {  //i represents the index
			curr = i;	
			temp = A[i];

			while ( curr >= gap && temp < A[curr-gap])  {
				
				*A = A[curr-gap];
				A[curr-gap] = curr;

			        curr = curr -gap;	
			}
		
			A[curr] = temp;
		}
	}
}

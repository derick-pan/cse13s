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
	int curr;
	int gap;

	for (int g = 0; g < GAPS; g= g+1){  //gap represents the value
		//set gap to the value
		gap = gaps[g];
		
		for (uint32_t i = gap ; i<n ; i+=1) {  //i represents the index
			curr = i;//Just a pointer/number	
			temp = A[i];//Hold that value i
			A[n+1] = A[n+1]+1;
			while ( curr >= gap && temp < A[curr-gap])  {
				A[n] = A[n]+1;
				A[curr] = A[curr-gap];
				A[curr-gap] = temp;

			        curr = curr -gap;	
			}
		
			A[curr] = temp;
		}
	}
}

//Derick Pan
//dpan7
//Asgn3 2021
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <gaps.h>

void shell_sort(unit32_t *A, unit32_t n) {
	int temp;
	int curr;
	int gap;
	int GapLen = sizeof(gaps)/sizeof(int);

	for (int g = 0; g < GapLen; g+=1){  //gap represents the value
		//set gap to the value
		gap = gaps[g];

		for (int i=g ; i<=n ; i+=1) {  //i represents the index
			curr = i;	
			temp = *A[i];

			while ( curr >= gap && temp < *A[curr-gap])  {
				
				*A = *[curr-gap];
				*A[curr-gap] = curr;

			        curr = curr -gap;	
			}
		
			*A[curr] = temp;
		}
	}
}

//Derick Pan
//dpan7
//Asgn3 2021
#include "bubble.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int moves;
int compares;
//This code is based off of Dr.Long's Pseudocode
                 //Pointer      //Size
void bubble_sort(uint32_t *A, uint32_t n) {
    moves = 0;
    compares = 0;
    int swapped = 1;
    while (swapped) {
        swapped = 0;
        for (uint32_t i = 1; i < n; i += 1) {
            compares += 1;	   //Keep track of the compares
            if (A[i] < A[i - 1]) {
                moves += 3;       //Keep track of the moves
                int temp = A[i];
                A[i] = A[i - 1];
                A[i - 1] = temp;
                swapped = 1;
            }
        }
        n -= 1;
    }

}

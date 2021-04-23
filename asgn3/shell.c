//Derick Pan
//dpan7
//Asgn3 2021
#include "shell.h"

#include "gaps.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
int moves;
int compares;
//This code is based off of Dr.Long's Pseudocode

void shell_sort(uint32_t *A, uint32_t n) {
    moves = 0;
    compares = 0;
    uint32_t temp;
    int curr;
    int gap;

    for (int g = 0; g < GAPS; g = g + 1) { //gap represents the value
        //set gap to the value
        gap = gaps[g];
        for (uint32_t i = gap; i < n; i += 1) { //i represents the index
            curr = i; //Just a pointer/number
            temp = A[i]; //Hold that value i
            compares += 1;
            while (curr >= gap && temp < A[curr - gap]) {
                moves += 3;
                A[curr] = A[curr - gap];
                curr = curr - gap;
            }
            moves += 1;
            A[curr] = temp;
        }
    }
}

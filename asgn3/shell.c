//Derick Pan
//dpan7
//Asgn3 2021
#include "shell.h"

#include "gaps.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
void shell_sort(uint32_t *A, uint32_t n) {
    int moves = 0;
    int compares = 0;
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
                A[curr - gap] = temp;

                curr = curr - gap;
            }

            A[curr] = temp;
        }
    }
    printf("Shell Sort\n%d elements, %d moves, %d compares\n", n, moves, compares);
}

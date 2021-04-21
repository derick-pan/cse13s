//Derick Pan
//dpan7
//Asgn3 2021
#include "bubble.h"
#include "queue.h"
#include "quick.h"
#include "shell.h"
#include "stack.h"

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int globalmoves;
int globalcompares;
int main(int argc, char **argv) {
    int flaga = 0; //All sorting Algorithms
    int flagb = 0; //Bubble sort
    int flags = 0; //Shell Sort
    int flagq = 0; //Stack
    int flagQ = 0; //Queue
    int flagn = 100; //Size
    int flagp = 100; //Elements to print
    int seed = 13371453;
    int choice;
    while ((choice = getopt(argc, argv, "absqQr:n:p:")) != -1) {
        switch (choice) {
        case 'a': flaga = 1; break;
        case 'b': flagb = 1; break;
        case 's': flags = 1; break;
        case 'q': flagq = 1; break;
        case 'Q': flagQ = 1; break;
        case 'r':
            if (optarg != NULL) {
                printf("%s\n", optarg);
                seed = atoi(optarg);
                break;
            }
            break;
        case 'n':
            if (optarg != NULL) {
                printf("%s\n", optarg);
                flagn = atoi(optarg);
                break;
            }
            break;
        case 'p':
            if (optarg != NULL) {
                printf("%s\n", optarg);
                flagp = atoi(optarg);
                break;
            }
            break;
        }
    }
    //To keep track of the # of moves and compares. I will add those two as elements in the list
    srandom(seed);
    uint32_t list[flagn];
    int i;
    for (int ind = 0; ind < flagn; ind = ind + 1) { //Create a list
        list[ind] = rand();
    }

    if (flagb == 1) { //If Bubble sort is chosen
        bubble_sort(list, sizeof(list) / sizeof(uint32_t));

        for (i = 0; i < flagp; i = i + 1) {
            printf("%13d", list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
    }
    if (flags == 1) { //If Shell sort is chosen
        shell_sort(list, sizeof(list) / sizeof(uint32_t));
        for (i = 0; i < flagp; i = i + 1) {
            printf("%13d", list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
    }
    if (flagq == 1) { //if flag Quick Sort (Stack) is chosen
        quick_sort_stack(list, sizeof(list) / sizeof(uint32_t));
        //printf("Max stack size: %d\n",stacksize);//Create a stacksize counter
        for (i = 0; i < flagp; i = i + 1) {
            printf("%13d", list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
    }
    if (flagQ == 1) { //if flag Quick Sort (Queue) is chosen
        quick_sort_queue(list, sizeof(list) / sizeof(uint32_t));
        printf("Quick Sort (Queue)\n%d elements, %d moves, %d compares\n", flagn, globalmoves,
            globalcompares);
        //printf("Max stack size: %d\n",stacksize);//Create a stacksize counter

        for (i = 0; i < flagp; i = i + 1) {
            printf("%13d", list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
    }
    return 1;
}

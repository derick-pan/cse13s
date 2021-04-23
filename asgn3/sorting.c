//Derick Pan
//dpan7
//Asgn3 2021
#include "bubble.h"
#include "queue.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stack.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char usage[800] = "Select at least one sort to perform.\n\
SYNOPSIS\n\tA collection of comparison-based sorting algorithms.\n\n\
USAGE\n\t\
   ./sorting [-absqQrnp] [-n length] [-p elements] [-r seed]\n\n\
OPTIONS\n\
\t-h              Display program help and usage.\n\
\t-a              Enable all sorts.\n\
\t-b              Enable Bubble Sort.\n\
\t-s              Enable Shell Sort.\n\
\t-q              Enable Quick Sort (Stack).\n\
\t-Q              Enable Quick Sort (Queue).\n\
\t-n length       Specify number of array elements.\n\
\t-p elements     Specify number of elements to print.\n\
\t-r seed         Specify random seed.\n";



int moves;
int compares;
uint32_t maxsize;

int main(int argc, char *argv[]) {
    int flagn = 100; //Size
    int flagp = 100; //Elements to print
    int seed = 13371453;
    int choice;
    char *test; //pointer for case r
    char *ntest; //pointer for case n
    uint32_t set = set_empty(); //Set is for the user arguments
    while ((choice = getopt(argc, argv, "absqQr:n:p:")) != -1) {
        switch (choice) {
        case 'a': set = set_insert(set, 16); break;
        case 'b': set = set_insert(set, 1); break;
        case 's': set = set_insert(set, 2); break;
        case 'q': set = set_insert(set, 4); break;
        case 'Q': set = set_insert(set, 8); break;
        case 'r':
            if (optarg != NULL) {
                seed = (int) strtoul(optarg, &test, 10);
            }
            break;
        case 'n':
            if (optarg != NULL) {
                flagn = (int) strtoul(optarg, &ntest, 10);
                if (optarg == ntest) {
                    fprintf(stderr, "Invalid array length.\n");
                    return 0;
                }
            }
            break;
        case 'p':
            if (optarg != NULL) {
                flagp = (int) strtoul(optarg, &test, 10);
            }
            break;
        case '?': fprintf(stderr, "%s", usage);
        }
    }
    if (argc < 2) { //If no arguments then print usage
        fprintf(stderr, "%s", usage);
        return 0;
    }
    if (flagp > flagn) { //If there are more things to print than array items, change the value
        flagp = flagn;
    }

    uint32_t list[flagn]; //Declaring the array of values
    int i;

    /*###########   IF BUBBLE SORT IS CHOSEN   #################################################### */
    if (set_member(set, 1) || set_member(set, 16)) {

        srandom(seed); // Initalize the seed and create a list.
        for (int ind = 0; ind < flagn; ind = ind + 1) {
            list[ind] = rand();
        }
        bubble_sort(list, sizeof(list) / sizeof(uint32_t)); // Call bubble sort
	
        printf("Bubble Sort\n%u elements, %d moves, %d compares\n", flagn, moves, compares);
        for (i = 0; i < flagp; i = i + 1) { // Iterate over the array items and print it.
            printf("%13" PRIu32, list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
    /*############################################################################################### */

    /*############   IF SHELL SORT IS CHOSEN   ###################################################### */
    if (set_member(set, 2) || set_member(set, 16)) { // If Shell Sort is Chosen

        srandom(seed); // Initalize the seed and create a list
        for (int ind = 0; ind < flagn; ind = ind + 1) {
            list[ind] = rand();
        }
        shell_sort(list, sizeof(list) / sizeof(uint32_t)); // Call the function then print it
        printf("Shell Sort\n%u elements, %d moves, %d compares\n", flagn, moves, compares);
        for (i = 0; i < flagp; i = i + 1) { // Iterate over the array items and print it.
            printf("%13" PRIu32, list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
    /*############################################################################################## */

    /*###########   IF STACK SORT IS CHOSEN   ###################################################### */
    if (set_member(set, 4) || set_member(set, 16)) { // if flag Quick Sort (Stack) is chosen

        srandom(seed); // Initalize the seed and create a list
        for (int ind = 0; ind < flagn; ind = ind + 1) {
            list[ind] = rand();
        }
        quick_sort_stack(list, sizeof(list) / sizeof(uint32_t)); // Call the function then print it
	printf("Quick Sort (Stack)\n%u elements, %d moves, %d compares\nMax stack size: %u\n", flagn, moves, compares,maxsize);
        for (i = 0; i < flagp; i = i + 1) {
            printf("%13" PRIu32, list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
    /*############################################################################################### */

    /*##########   IF QUEUE SORT IS CHOSEN   ######################################################## */
    if (set_member(set, 8) || set_member(set, 16)) { // if flag Quick Sort (Queue) is chosen
        srandom(seed);
        for (int ind = 0; ind < flagn; ind = ind + 1) { // Initalize the seed and Create a list
            list[ind] = rand();
        }
        quick_sort_queue(list, sizeof(list) / sizeof(uint32_t)); // Call the function then print it.
	printf("Quick Sort (Queue)\n%u elements, %d moves, %d compares\nMax stack size: %u\n", flagn, moves, compares,maxsize);
        for (i = 0; i < flagp; i = i + 1) {
            printf("%13" PRIu32, list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
        printf("\n");
    }
    /*############################################################################################### */

    return 1;
}

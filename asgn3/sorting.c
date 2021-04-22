//Derick Pan
//dpan7
//Asgn3 2021
#include "bubble.h"
#include "queue.h"
#include "quick.h"
#include "shell.h"
#include "stack.h"
#include "set.h"
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    int flagn = 100; //Size
    int flagp = 100; //Elements to print
    int seed = 13371453;
    int choice;
    uint32_t set = set_empty();
    while ((choice = getopt(argc, argv, "absqQr:n:p:")) != -1) {
        switch (choice) {
        case 'a': 
	    set = set_insert(set, 16);
	    break;
        case 'b':
	    set = set_insert(set, 1); 
	    break;
        case 's':
	    set = set_insert(set, 2); 
	    break;
        case 'q':
	    set = set_insert(set, 4); 
	    break;
        case 'Q':
	    set = set_insert(set, 8); 
	    break;
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
	default: 
	    fprintf(stderr, "um");
        }
    }
    //To keep track of the # of moves and compares. I will add those two as elements in the list
    uint32_t list[flagn];
    int i;

    if (set_member(set, 1) || set_member(set,16)) { //If Bubble sort is chosen
	    srandom(seed);
	    for (int ind = 0; ind < flagn; ind = ind + 1) { //Create a list
		list[ind] = rand();
	    }
        bubble_sort(list, sizeof(list) / sizeof(uint32_t));

        for (i = 0; i < flagp; i = i + 1) {
            printf("%13" PRIu32, list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
    }
    if (set_member(set, 2) || set_member(set,16)) { //If Shell sort is chosen
	    srandom(seed);
	    for (int ind = 0; ind < flagn; ind = ind + 1) { //Create a list
		list[ind] = rand();
	    }
        shell_sort(list, sizeof(list) / sizeof(uint32_t));
        for (i = 0; i < flagp; i = i + 1) {
            printf("%13" PRIu32, list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
    }
    if (set_member(set,4) || set_member(set,16)) { //if flag Quick Sort (Stack) is chosen
    srandom(seed);
    for (int ind = 0; ind < flagn; ind = ind + 1) { //Create a list
        list[ind] = rand();
    }
        quick_sort_stack(list, sizeof(list) / sizeof(uint32_t));
        for (i = 0; i < flagp; i = i + 1) {
            printf("%13" PRIu32, list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
    }

    if (set_member(set,8) || set_member(set,16) ) { //if flag Quick Sort (Queue) is chosen
    srandom(seed);
    for (int ind = 0; ind < flagn; ind = ind + 1) { //Create a list
        list[ind] = rand();
    }
        quick_sort_queue(list, sizeof(list) / sizeof(uint32_t));
        for (i = 0; i < flagp; i = i + 1) {
            printf("%13" PRIu32, list[i]);
            if ((i + 1) % 5 == 0) {
                printf("\n");
            }
        }
    }
    return 1;
}

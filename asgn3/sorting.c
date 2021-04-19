//Derick Pan
//dpan7
//Asgn3 2021
#include "bubble.h"
#include "shell.h"
#include "quick.h"
#include "stack.h"
#include "queue.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
int main(int argc, char **argv) {
	int flaga = 0;//All sorting Algorithms
	int flagb = 0;//Bubble sort
	int flags = 0;//Shell Sort
	int flagq = 0;//Stack
	int flagQ = 0;//Queue
	int flagn = 100;//Size
	int flagp = 100;//Elements to print
	int seed = 13371453;
	int choice;
	while((choice = getopt(argc,argv, "absqQr:n:p:")) != -1) {

		switch(choice) {
		case 'a':
			flaga = 1;
		case 'b':
			flagb = 1;
			break;
		case 's':
			flags = 1;
			break;
		case 'q':
			flagq = 1;
		case 'Q':
			flagQ = 1;
		case 'r':
			if (optarg != NULL) {
				printf("%s\n",optarg);
				seed = atoi(optarg);
				break;
			}
			break;
			
		case 'n':
			if (optarg != NULL) {
				printf("%s\n",optarg);
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
	srandom(seed);
	uint32_t list[flagn];
	int i;
	for(int ind=0; ind < flagn ; ind= ind+1){ //Create a list
		list[ind] = rand();
	}
	if(flagb ==1){ //If Bubble sort is chosen 
		bubble_sort(list, sizeof(list)/sizeof(uint32_t));
		printf("%d\n",list[0]);
		for (i = 0; i <= flagp ; i = i+1) {
			
			printf("bubble: %d\n", list[i]);
		}		
	}

	if(flags ==1) {//If Shell sort is chosen
		shell_sort(list, sizeof(list)/sizeof(uint32_t));
			
		for (i = 0; i <= flagp ; i = i+1) {
			printf("Shell: %d\n", list[i]);
		}
	}	


	return 1;
}


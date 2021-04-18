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
int main(int argc, char **argv) {
	int flaga = 0;//All sorting Algorithms
	int flagb = 0;//Bubble sort
	int flags = 0;//Shell Sort
	int flagq = 0;//Stack
	int flagQ = 0;//Queue
	int flagn = 100;//Size
	int flagp = 100;//Elements to print
	int choice;
	while((choice = getopt(argc,argv, "absqQr:n:p:")) != -1) {

		switch(choice) {
		case 'a':
			flaga = 1;
		case 'b':
			flagb = 1;
		case 's':
			flags = 1;
		case 'q':
			flagq = 1;
		case 'Q':
			flagQ = 1;
		case 'r':
			if (optarg != NULL) {
				srandom((uint32_t) strtoul(optarg,NULL,10));
			}
			else{srandom(13371453);}
		case 'n':
			if (optarg != NULL) {
				flagn = (uint32_t) strtoul(optarg,NULL,10);
				break;
			}
		case 'p':
			if (optarg != NULL) {
				flagp = (uint32_t) strtoul(optarg,NULL,10);
				break;
			}
		}
	}
	
	uint32_t list[flagn];

	for(int ind=0; ind <= flagn; ind= ind+1){ //Create a list
		list[ind] = rand();
	}

	if(flagb ==1){ //If Bubble sort is chosen 

		bubble_sort(list, sizeof(list)/sizeof(uint32_t));

		int size = sizeof(list)/sizeof(int);

		for (int i = 0; i < size ; i = i+1) {
			printf("Index: %p. Value: %d\n",(void *) &list[i], list[i]);
		}		
	}
	return 1;
}


//Derick Pan
//dpan7
//Asgn3 2021
#include "bubble.h"
#include "gaps.h"
#include "shell.h"
#include "quick.h"
#include "stack.h"
#include "queue.h"
#include <unistd.h>
#include <stdio.h>

int main() {
	int flaga = 0;//All sorting Algorithms
	int flagb = 0;//Bubble sort
	int flags = 0;//Shell Sort
	int flagq = 0;//Stack
	int flagQ = 0;//Queue
	int flagr = 13371453;//seed
	int flagn = 100;//Size
	int flagp = 100;//Elements to print
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
			if (optarg != NULL && optarg >0) {
				srandom(optarg);
				break;
			}
			srandom(13371453);
		case 'n':
			if (optarg != NULL && optarg >0) {
				flagn = optarg;
				break;
			}
		case 'p':
			if (optarg != NULL && optarg >0) {
				flagp = optarg;
				break;
			}
		}
	}
	if(flagb ==1){
		int x[8] = {123,16,89,632,1,97,45,29};
		bubble_sort(x, sizeof(x)/sizeof(int);
		
		for (int i = 0; i< sizeof(x); i++) {
			printf("Index: %p. Value: %d", x, *x[i]);
		}		
	}


}
		



















	return 1;










}


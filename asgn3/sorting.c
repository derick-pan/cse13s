//Derick Pan
//dpan7
//Asgn3 2021
#include "bubble.h"
#include "gaps.h"
#include "shell.h"
#include "quick.h"
#include "stack.h"
#include "queue.h"

int main() {
	flaga = 0;//All sorting Algorithms
	flagb = 0;//Bubble sort
	flags = 0;//Shell Sort
	flagq = 0;//Stack
	flagQ = 0;//Queue
		flagr = 13371453;//seed
	flagn = 100;//Size
	flagp = 100;//Elements to print
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
		float x[8] = {123,16,89,632,1,97,45,29};
		bubble_sort(sizeof(x), x)}
}
		



















	return 1;










}


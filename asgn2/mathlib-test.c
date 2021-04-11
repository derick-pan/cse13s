#include <stdio.h>
#include <unistd.h>
#include "mathlib.h"
#include <math.h>
int main(int argc, char *argv[]) {

    int choice;

	double libr;
    while ((choice = getopt(argc, argv, "ascti")) != -1) {
        double x;
        switch (choice) {
        case 's':
            for (x = -1; x < 1; x += 0.100000000) {
		libr = asin(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,arcSin(x) , libr, arcSin(x)-libr);
            }
	case 'c':
	    for (x = -1; x <1; x += 0.1) {
		libr = acos(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,arcCos(x) , libr, arcCos(x)-libr);
            }
            break;

        /*
                        case 's':

                        case 'c':

                        case 't':
    
                        case 'i':    
			    */
        default: fprintf(stderr, "print the program usage?");
        }
    }
    return 0;
}

#include <stdio.h>
#include <unistd.h>
#include "mathlib.h"
int main(int argc, char *argv[]) {

    int choice;

    while ((choice = getopt(argc, argv, "ascti")) != -1) {
        double x;
        switch (choice) {
        case 'a':
            for (x = -1; x < 1; x += 0.100000000) {
                printf("%.8lf\n", arcSin(x));
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

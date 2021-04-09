#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]) {

    int choice;

    while ((choice = getopt(argc, argv, "ascti")) != -1) {
        double x;
        double increment = 0.1;
        switch (choice) {
        case 'a':
            for (x = -1; x < 1; x += increment) {
                printf("%lf", x);
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

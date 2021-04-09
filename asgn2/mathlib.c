#include "mathlib.h"

#include <math.h>
#include <stdio.h>

double ffactorial(double base) { //Function to simplify Factorials
    double ans = 1;
    double i = 1;
    for (i = 1; i <= base; i++) {
        ans = ans * i
    }
    return ans;
}

double paower(double base, double top) { //Function to simplify to powers
    double ans = 1;
    double i = 1;
    for (i = 1; i <= top; i++) {
        ans = ans * base;
    }
    return ans;
}
int main(int argc, char **argv[]) {

	int choice;

	while (( choice = getopt(argc,argv, "ascti" )) != -1) {

		switch (choice) {
			case 'a':
			
			case 's':

			case 'c':

			case 't':
			
			case 'i':	
			
			default:
				fprintf(stderr, "print the program usage?");
		}
	}
}
double arcSin() {
    double x = -1

               for (x = -1; x < 1; x + 0.1) { //Increment X from -1 to 1, step 0.1

        double k = 0;
        for (k = 0; 0; k++) { //Taylor Expansion
            double tk = 2 * k;
            double factk = ffactorial(k);
            double facttk = ffactorial(tk);

            double arcCos() {

                double arcTan() {

                    double Log() {

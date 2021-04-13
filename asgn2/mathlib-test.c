//Derick Pan
//dpan7
//Asgn2 2021
#include <stdio.h>
#include <unistd.h>
#include "mathlib.h"
#include <math.h>
//This is the test harness for the mathlib implementations.
//The following are 5 flags, a for all tests, s= sin, c=cos, t=tan, l=log
//The flags are set to 0, and if they change to 1, it means that the user selected that choice
int main(int argc, char *argv[]) {
	int flaga = 0;
	int flags = 0;
	int flagc = 0;
	int flagt = 0;
	int flagl = 0;
    double libr;
    int choice;
    
    while ((choice = getopt(argc, argv, "asctl")) != -1) {//Loop that goes over the user inputs
        switch (choice) {
        case 'a':
		flaga = 1;
		break;	
        case 's':
		flags = 1;
		   break;
	case 'c':
		flagc = 1;
		   break;
	case 't':
		flagt = 1;
		   break;
	case 'l':
		flagl = 1;
	   break;
	case '?'://If unrecognized input,print usage, then break
	    printf("Program usage: ./mathlib - [asctl]\n");
	    printf("   -a   Runs all tests (arcsin, arccos, arctan, log\n");
	    printf("   -s   Runs arcsin tests\n");
	    printf("   -c   Runs arccos tests\n");
	    printf("   -t   Runs arctan tests\n");
	    fprintf(stderr,"   -l   Runs log tests\n");
	    break;
	case ':'://If unrecognized input then break
	    break;
        }
    }
    //If input is invalid, then print program usage
    if (argv[optind] == NULL || argv[optind +1] == NULL) {
	    printf("Program usage: ./mathlib - [asctl]\n");
	    printf("   -a   Runs all tests (arcsin, arccos, arctan, log\n");
	    printf("   -s   Runs arcsin tests\n");
	    printf("   -c   Runs arccos tests\n");
	    printf("   -t   Runs arctan tests\n");
	    fprintf(stderr,"   -l   Runs log tests\n");
    }
  double x;//This x is the value to pass onto the functions

  if (flaga== 1 || flags ==1) { //If all test's flag or arcsin flag is ==1, then print values from -1 to 1, w/ step 0.1
                printf("  x\t       arcSin\t\tLibrary\t       Difference\n" ); 
                printf("  -\t       ------\t\t-------\t       ----------\n" ); 
            for (x = -1; x < 1; x += 0.100000000) {
		libr = asin(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,arcSin(x) , libr, arcSin(x)-libr);
            }
	 }
 if(flaga==1 || flagc == 1) { //If all test's flag or arccos flag is ==1, then print values from -1 to 1, w/ step 0.1
                printf("  x\t       arcCos\t\tLibrary\t       Difference\n" ); 
                printf("  -\t       ------\t\t-------\t       ----------\n" ); 
	    for (x = -1; x <1; x += 0.1) {
		libr = acos(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,arcCos(x) , libr, arcCos(x)-libr);
            }
 }
 if(flaga==1 || flagt == 1) {//If all test's flag or acrcos flag is ==1, then print values from 1 to 10, w/ step 0.1
                printf("  x\t       arcTan\t\tLibrary\t       Difference\n" ); 
                printf("  -\t       ------\t\t-------\t       ----------\n" ); 
	    for (x = 1; x <10; x += 0.1) {
		libr = atan(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,arcTan(x) , libr, arcTan(x)-libr);
            }
 }
 if(flaga==1 || flagl == 1) { //If all test's flag or log flag is ==1, then print values from 1 to 10, w/ step 0.1
                printf("  x\t       Log   \t\tLibrary\t       Difference\n" ); 
                printf("  -\t       ------\t\t-------\t       ----------\n" ); 
	    for (x = 1; x <10; x += 0.1) {
		libr = log(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,Log(x) , libr, Log(x)-libr);
            }
 }

    return 0;
}

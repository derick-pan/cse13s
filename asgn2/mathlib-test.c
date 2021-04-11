#include <stdio.h>
#include <unistd.h>
#include "mathlib.h"
#include <math.h>
int main(int argc, char *argv[]) {
	int flaga = 0;
	int flags = 0;
	int flagc = 0;
	int flagt = 0;
	int flagl = 0;
    double libr;
    int choice;
    while ((choice = getopt(argc, argv, "asctl")) != -1) {
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
	case '?':
	    printf("Program usage: ./mathlib - [asctl]\n");
	    printf("   -a   Runs all tests (arcsin, arccos, arctan, log\n");
	    printf("   -s   Runs arcsin tests\n");
	    printf("   -c   Runs arccos tests\n");
	    printf("   -t   Runs arctan tests\n");
	    fprintf(stderr,"   -l   Runs log tests\n");
	    break;
	
        }
    }
  double x;
  if (flaga== 1 || flags ==1) { 
                printf("  x\t       arcSin\t\tLibrary\t       Difference\n" ); 
                printf("  -\t       ------\t\t-------\t       ----------\n" ); 
            for (x = -1; x < 1; x += 0.100000000) {
		libr = asin(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,arcSin(x) , libr, arcSin(x)-libr);
            }
	 }
 if(flaga==1 || flagc == 1) {
                printf("  x\t       arcCos\t\tLibrary\t       Difference\n" ); 
                printf("  -\t       ------\t\t-------\t       ----------\n" ); 
	    for (x = -1; x <1; x += 0.1) {
		libr = acos(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,arcCos(x) , libr, arcCos(x)-libr);
            }
 }
 if(flaga==1 || flagt == 1) {
                printf("  x\t       arcTan\t\tLibrary\t       Difference\n" ); 
                printf("  -\t       ------\t\t-------\t       ----------\n" ); 
	    for (x = 1; x <10; x += 0.1) {
		libr = atan(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,arcTan(x) , libr, arcTan(x)-libr);
            }
 }
 if(flaga==1 || flagl == 1) {
                printf("  x\t       Log   \t\tLibrary\t       Difference\n" ); 
                printf("  -\t       ------\t\t-------\t       ----------\n" ); 
	    for (x = 1; x <10; x += 0.1) {
		libr = log(x);
                printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n",x ,Log(x) , libr, Log(x)-libr);
            }
 }
    return 0;
}

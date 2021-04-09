#include "mathlib.h"
#include <mathlib-test.c>
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

double epsilonn = paower(10, -10);

double arcSin(double x) {
    //double x = -1;
    //for (x = -1; x < 1; x + 0.1) { //Increment X from -1 to 1, step 0.1
	//double Finalans = x;
        //double k = 0;
	double Finalans = x;
	double k = 0;	
        for (k = 0; 0; k++) { //Taylor Expansion
            double tk = 2 * k;
            double factk = ffactorial(k);
            double facttk = ffactorial(tk);
	    double numerator = facttk * paower(x, tk+1);
	    double denominator = paower(2, tk) * paower(factk,2) *(tk+1);
	    double tempans = numerator/denominator;
	    Finalans = tempans + Finalans;
	    if (x-Finalans <= epsilonn) {
		    return Finalans;
        }
    return 1;
}

double arcCos() {
}
double arcTan() {
}
double Log() {
}

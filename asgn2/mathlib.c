#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "mathlib.h"
//mathlib.c//
/*
double ffactorial(double base) { //Function to simplify Factorials
    double ans = 1;
    double i = 1;
    for (i = 1; i <= base; i++) {
        ans = ans * i;
	//printf("kms ffactorial");
    }
    return ans;
}

double paower(double base, double top) { //Function to simplify to powers
    double ans = base;
    int exp= (int)top;
    for (;;) {
	if (exp <= 0) {
		return ans; }
	exp = exp - 1;
        ans = ans * base;
	printf("kms paower");
    }
    return ans;
}
*/
//temporary Will create own
double abss(double val) {
	return val < 0 ? -val : val;
}
double epsilonn = 0.000000001;
double arcSin(double x) {
    double Finalans = x;
    double k = 0;
    double top = 1;
    double bot = 2;
    double ex = x*x*x;
    double exbot = 3;
    double leftpass = 1;
    double testans = 0;
    for (;;) { //Taylor Expansion
	leftpass = leftpass * (top/bot);
	Finalans = Finalans+(leftpass * (ex/exbot));
	k = k + 1; 
	ex = ex*x*x;
	exbot = exbot+2;
	bot = bot +2;
	top = top +2;
        if (abss(abss(Finalans) - abss(testans)) < epsilonn) {
            return Finalans;
	}
    testans = Finalans;
    }
    return 1;
}

double arcCos(double x) {
	return ((M_PI/2) - arcSin(x));
    return 0;
}
double arcTan(double x) {
	
	for(;;) {//something * something = under sqrt.  difference of epsilon  


	return ((arcSin(x/botsq)));
    return 0;
}
double Log() {
    return 0;
}

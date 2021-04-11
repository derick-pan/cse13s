#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "mathlib.h"
//mathlib.c//
double epsilonn = 0.000000001;


double abss(double val) {
	if (val < 0) {
	    val = val * -1;
	    return val;
	}
	return val;
}
double Exp(double x) { //Exp() function is from Professor Long
	double term = 1, sum = 1;
	for (int k = 1; abss(term) > epsilonn; k += 1) {
		term *= x/k;
		sum += term;
	}
	return sum;
}
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
	
	double below = (x*x) + 1;
	double test = below;
	double finalans = below;
	for(;;) {
	    test = finalans;
	    finalans= ((test + below/test)/2);//Newtons method
	    if (abss(abss(finalans)-abss(test)) < 0.00000000001) {
		return (arcSin(x/finalans));
   	    }
        }	    
	return 0;
}
double Log(double x) {
	double pass = 1;
	double epow;
	for(;;) {
	    	epow = Exp(pass);
		pass = pass + (abss(x) - epow)/epow;
	    	if (abss(abss(x) - abss(epow)) < epsilonn){
			return pass;
		}
	}




    return 0;
    


}

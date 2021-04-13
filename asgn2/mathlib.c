//Derick Pan
//dpan7
//Asgn2 2021
#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
double epsilonn = 0.000000001;

double abss(double val) { //Returns the absolute value
    if (val < 0) {
        val = val * -1;
        return val;
    }
    return val;
}
double Exp(double x) { //Exp() function is from Professor Long
    double term = 1, sum = 1;
    for (int k = 1; abss(term) > epsilonn; k += 1) {
        term *= x / k;
        sum += term;
    }
    return sum;
}
double arcSin(double x) { // Calculates arcSin(x) through a simplified Maclaurin Series
    double Finalans = x; //The current iteration's answer.
    double k = 0; //Counter for # of iterations. This isn't printed but is nice to have
    double top = 1; //Top is the lefthand side numerator             EXPLAINED IN DESIGN.pdf
    double bot = 2; //Bot is the lefthand side denominator           EXPLAINED IN DESIGN.pdf
    double ex = x * x * x; //exp is the right hand side's numerator's simplified power
    double exbot = 3; //exbot is the right hand side denominator.	  EXPLAINED IN DESIGN.pdf
    double leftpass = 1; //Leftpass is the current iteration's left side  EXPLAINED IN DESIGN.pdf
    double testans = 0; //testans is the previous iteration's answer     EXPLAINED IN DESIGN.pdf

    for (;;) { //Taylor Expansion
        leftpass = leftpass * (top / bot); //Multiply the previous left sides by top/bot
        Finalans = Finalans + (leftpass * (ex / exbot)); //Get the current answer
        k = k + 1; //Counter +=1
        ex = ex * x * x; //After each iteration, multiply x*x*ex
        exbot = exbot + 2; //Right side denominator +2 for the pattern.
        bot = bot + 2; //Left side denominator +2 for the pattern.
        top = top + 2; //Left side Numerator +2 for the pattern
        if (abss(abss(Finalans) - abss(testans))
            < epsilonn) { //test if the difference from current and last ieration < epsilon
            return Finalans;
        }
        testans = Finalans;
    }
    return 1;
}

double arcCos(double x) { //arcCos found by subtracting arcSin(x) from Pi/2.
    return ((M_PI / 2) - arcSin(x));
    return 0;
}
double arcTan(double x) { //Arctan found by arcsin(x/sqrt(x*x+1))

    double below = (x * x) + 1; //Below is the value getting passed to arcsin's denominator
    double test = below; //Test is the answer from previous iteration for Square rooting
    double finalans = below; //Finalans is the Current Answer for square rooting
    for (;;) {
        test = finalans; //Set the previous value to test.
        finalans
            = ((test + below / test) / 2); //Newtons method   //Find the current iterations number
        if (abss(abss(finalans) - abss(test))
            < epsilonn) { //If the difference from finalans and test is less than epsilon,
            //Then that is close to the square root.
            return (arcSin(x / finalans)); //Return arcsin(x/finalans)
        }
    }
    return 0;
}
double Log(double x) {
    double pass = 1;
    double epow; //Declare the e^ xk. This is declared because it's used TWICE in an iteration.
    for (;;) {
        epow = Exp(pass); //Find epow once, and it will be used TWICE in the following.
        pass = pass + (abss(x) - epow) / epow; //Pass is the current ans
        if (abss(abss(x) - abss(epow)) < epsilonn) { //Test if difference is less than epsilon
            return pass; //Return the value.
        }
    }

    return 0;
}

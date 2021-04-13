Derick Pan
dpan7
Spring 2021
Asgn 2: A Small Numerical Library

--------------------------------
DESCRIPTION

This C code is my implementation of arcSin(x), arcCos(x), arcTan(x), Log(x).
Using Maclaurin Series, Newton's method, and many loops.
In my code, <math.h> was only used to define PI, and to print the math.h version of the math functions.

--------------------------------
FILES

-mathlib.h
-mathlib.c
-mathlib-test.c
-Makefile
-README.md
-DESIGN.pdf
-WRITEUP.pdf

--------------------------------
INSTRUCTIONS

To run these files, download these files on a machine that runs the lastest version of Ubuntu.
Then open a terminal and type "make". This will compile the code for usage. Then type "./mathlib"
to view the options to run the code.

The avaliable options for mathlib are as follows:
-a : to run all tests.
-s : to run arcsin tests.
-c : to run arccos tests.
-t : to run arctan tests.
-l : to run log tests.
~~~~~~~~~~~~~~~~~~~~~~
Here's an example of how to run arcsin and arccos tests.
./mathlib -s -c


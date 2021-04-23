Derick Pan
dpan7
Spring 2021
Asgn 3: Sorting: Putting your affairs in order

--------------------------------
DESCRIPTION

This C code is my implementation of Bubble sort, Shell sort, and Quicksort through Stack and Queue. 
These implementations were done most in part of following Dr.Long's Pseudocode.

Bubble Sort:
Works by testing adjacent pairs of items, and swapping the items if it swaps to ascending order. 
It'll keep swapping till the condition isn't true anymore, so bubbling to the top.
	
Shell Sort:
Works by testing elements a gap length apart then shortening the gap and testing those values. 
The gap sequence used in this code is the Pratt sequence.
	
Quicksort (Stack) (Queue):
Both Stack and Queue's implmentation follow the same format of using a partition function that 
organizes an array with respect to it's pivot position. The only difference between the two is that 
Stack uses a stack, and Queue uses a queue.

--------------------------------
FILES

-bubble.h 
-bubble.c
-gaps.h
-shell.h
-shell.c
-quick.h
-quick.c
-stack.h
-stack.c
-set.h
-set.c
-queue.h
-queue.c
-sorting.c
-Makefile
-README.md
-DESIGN.pdf
-WRITEUP.pdf

---------------------------------
INSTRUCTIONS

To run these files, download these files on a machine that runs the lastest version of Ubuntu.
Then open a terminal and type "make". This will compile the code and create an executable. 
If you want to only format the code then run "make format"
Then type "./sorting"

to view the options to run the code, also shown following:

    ./sorting [-absqQrnp] [-n length] [-p elements] [-r seed]

OPTIONS\n\
-h              Display program help and usage.
-a              Enable all sorts.
-b              Enable Bubble Sort.
-s              Enable Shell Sort.
-q              Enable Quick Sort (Stack).
-Q              Enable Quick Sort (Queue).
-n length       Specify number of array elements.
-p elements     Specify number of elements to print.
-r seed         Specify random seed.








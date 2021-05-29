Derick Pan
dpan7
Spring 2021
Asgn7: The Great Firewall of Santa Cruz

---------------------------------------------
DESCRIPTION

In this assignment, we have been chosen by the Dear and Beloved Leader
of the Glorious People's Republic of Santa Cruz ( GPRSC ) to in a nutshell, 
implement a filter to discourage language we decide wrong. We do this by using
a bloom filter, to test whether or not a word is in our set. We could have 
false-positives but NEVER false negatives. We hash the words using the Speck Cipher,
and keep track of them using Bit vectors. The hash table is what we use to hash, 
and to avoid hash collisions, we use a doubly Linked Lists to deal with it.
The executable should take in a file through stdin, and test each word, including
hyphenated and words with ' . If the test comes up as a badspeak word or a word that
requires newspeak. We will correct them and inform them of their misdeeds.

-----------------------------------------------------
FILES

- banhammer.c
- messages.h
- speck.h
- speck.c
- ht.h
- ht.c 
- ll.h
- ll.c
- node.h
- node.c
- bf.h
- bf.c 
- bv.h
- bv.c
- parser.h
- parser.c
- Makefile
- README.md
- DESIGN.pdf
- WRITEUP.pdf

----------------------------------------------------
INSTRUCTIONS

To run these files, download these files on a machine that runs the lastest
version of Ubuntu. Then open a terminal and type "make all". This will compile 
the code and create several executables.
make all or make will build the banhammer executable
make clean will remove all files created from make
make format will format all the code
=========================================

SYNOPSIS
  A word filtering program for the GPRSC.
  Filters out and reports bad words parsed from stdin.

USAGE
  ./banhammer [-hsm] [-t size] [-f size]

OPTIONS
  -h           Program usage and help.
  -s           Print program statistics.
  -m           Enable move-to-front rule.
  -t size      Specify hash table size (default: 10000).
  -f size      Specify Bloom filter size (default: 2^20).

==========================================


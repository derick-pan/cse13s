Derick Pan
dpan7
Spring 2021
Asgn6: Huffman Coding

---------------------------------------------
DESCRIPTION
	This assignment is about encoding and decoding through Huffman Coding. Huffman coding algorithm
is a type of Data Compression to compress data without losing any information. It's based on creating
codes based on the frequency of an ascii+extended frequencies. I create a code tree, where the leaf
nodes are the characters in the file to encode, and the interior nodes are the parents to those nodes.
To go through this tree I traverse through through the tree, traversing left has code 0, and traversing right
has code 1. Traveling through the entire tree to a leaf node would add up to the code of the symbol.
In order to decode my Huffman encoded file: I confirm that the file was encoded through huffman by a
secret variable called "0xDEADBEEF" Once I confirm that the file is legit, I read through the tree dump to
recreate the huffman tree, then read through the codes of the file to eventually come up with the decoded file.

-----------------------------------------------------
IMPORANT
	The Encoder will create and destory a file name "t3mp0r6rY_hOIdlng_fi1e" if you choose to use
stdin to encode something rather than supplying a file. If there's a slim change you already have a
file named "t3mp0r6rY_hOIdlng_fi1e" Please back it up or else it will be destroyed.
					You have been warned
-----------------------------------------------------
FILES

-encode.c
-decode.c
-entropy.c
-defines.h
-header.h
-node.h
-node.c
-pq.h
-pq.c
-code.h
-code.c
-io.h
-io.c
-stack.c
-stack.h
-huffman.h
-huffman.c
-Makefile
-README.md
-DESIGN.pdf


----------------------------------------------------
INSTRUCTIONS

To run these files, download these files on a machine that runs the lastest
 version of Ubuntu. Then open a terminal and type "make all". This will compile 
the code and create several executables.
Make encode will build just the encoder
Make decode will build just the decoder
Make entropy will build just the supplied entropy-measure program
make clean will remove all files created from make
make format will format all the code
=========================================
ENCODE:
SYNOPSIS
  A Huffman encoder.
  Compresses a file using the Huffman coding algorithm.

USAGE
  ./encode [-h] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -v             Print compression statistics.
  -i infile      Input file to compress.
  -o outfile     Output of compressed data.

  
==========================================
SYNOPSIS
  A Huffman decoder.
  Decompresses a file using the Huffman coding algorithm.

USAGE
  ./decode [-h] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -v             Print compression statistics.
  -i infile      Input file to decompress.
  -o outfile     Output of decompressed data.
==========================================

These two files will encode and or decode at your will using command
arguments.

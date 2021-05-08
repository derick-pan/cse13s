Derick Pan
dpan7
Spring 2021
Asgn 5: Hamming Codes

---------------------------------------------
DESCRIPTION
	This assignment is about encoding and decoding through Hamming codes. Using Hamming(8,4) that 
Within the hamming codes there are parity bits and data bits. To encode a message( four bits) we multiply
that message as a matrix to the generator matrix. The result is a 1 byte code. The generator matrix is a 4x8.
The left side of the matrix is an identity matrix that ensures the first four bits of the Hamming code are 
data bits, while the right half is used to calculate the parity of the message.
To decode, we multiply the code by a DIFFERENT generator matrix. This generator matrix is the transposed matrix
of the one used to encode a message. We multiply the code by the Transposed matrix to get a 4 bit matrix. If
the matrix is 0000, then there are no errors, and if it's different we use the lookup table detailed in the DESIGN
and the hamming.c to see if it's a correctable error or a non-correctable error. We have the option to inject error
into the decoder, to see how much noise can be injected and how much is decodeable.


-----------------------------------------------------
FILES

-encode.c
-decode.c
-error.c
-entropy.c
-bv.h
-bv.c
-bm.h
-bm.c
-hamming.h
-hamming.c
-Makefile
-README.md
-DESIGN.pdf

----------------------------------------------------
INSTRUCTIONS

To run these files, download these files on a machine that runs the lastest
 version of Ubuntu. Then open a terminal and type "make all". This will compile 
the code and create an executable.
Make encode will build just the encoder
Make decode will build just the decoder
make error will build just the supplied error-injection program
Make entropy will build just the supplied entropy-measure program
make clean will remove all files created from Make
make format will format all the code
=========================================
ENCODE:
SYNOPSIS
  A Hamming(8, 4) systematic code generator.

USAGE
  ./encode [-h] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -i infile      Input data to encode.
  -o outfile     Output of encoded data.
  
==========================================
DECODE:
SYNOPSIS
  A Hamming(8, 4) systematic code decoder.

USAGE
  ./decode [-h] [-v] [-i infile] [-o outfile]

OPTIONS
  -h             Program usage and help.
  -v             Print statistics of decoding to stderr.
  -i infile      Input data to decode.
  -o outfile     Output of decoded data.
==========================================

These two files will encode and or decode at your will using command
arguments.



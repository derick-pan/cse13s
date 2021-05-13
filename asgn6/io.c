//Derick Pan
//dpan7
//io.c
#include "io.h"

#include "code.c"

#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern uint64_t bytes_read;
extern uint64_t bytes_written;
//Block = 4096
static uint8_t buf[BLOCK]; //Declare buffer in io.c
static int bufind = 0; //Declare buffer index

//3977/8 = 497.125   gotta be 498

//3977 % 8 = 1     3977/8 +1 = 498

//3948 / 8 = 493.5  gotta be 494
//  if (3948 % 8 > 1) 3948/8 +1 = 494
int read_bytes(int infile, uint8_t *buf, int nbytes) { //Internal function
    //uint64_t bytes_read; //Total num of bytes read from infile
    int bytes; //Number of bytes read
    // -1,0 is the error return , so set it greater than 0
    //May cause issues
    while ((bytes = read(infile, buf, nbytes)) > 0 && (int) bytes_read != nbytes) {
        buf += bytes; //Increase position of buffer
        bytes_read += bytes;
    }
    return bytes_read;
}

//Internal Function
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    //int bytes_written; //Total num of bytes written to outfile
    int bytes; //Number of bytes written in one write
    // -1,0 is the error return , so set it greater than 0
    while ((bytes = write(outfile, buf, nbytes)) > 0 && (int) bytes_written != nbytes) {
        buf += bytes; //Increase position of buffer
        bytes_written += bytes;
    }
    return bytes_written;
}

//External Function
bool read_bit(int infile, uint8_t *bit) { //Calls read_bytes, used in main
    //Uses functionality of read_bytes

    //if buffer empty or the buffer's index is the size of a block
    //Or if the index is 0, meaning buffer is empty
    if (bufind == BLOCK || bufind == 0) {
        //Fill the buffer if fillable
        if (read_bytes(infile, buf, BLOCK) == 0) {
            return false;
        }
        bufind = 0;
    }
    //pass back bit at bufind
    *bit = (buf[bufind / 8] >> (bufind % 8) & 0x1); //Get the bit
    bufind += 1;
    return true;
}

//External Function
void write_code(int outfile, Code *c) { //calls write bytes , used in main
    //Each bit in the code c is buffered into the buffer
    //Create a loop to iterate over the buffer

    //Code is based off of Euguene's Pseudocode
    for (uint32_t i = 0; i < c->top; i++) {

        if (code_get_bit(c, i) == 1) {
            //Set the bit to 1 at buffer
            buf[bufind / 8] |= 0x1 << (bufind % 8);
        } else {
            //Set the bit to 0 at the buffer location
            buf[bufind / 8] &= ~(0x1 << (bufind % 8));
        }
        bufind += 1;

        //If the index
        if (bufind == BLOCK) {
            //Fill the buffer if fillable
            write_bytes(outfile, buf, BLOCK);
            bufind = 0;
        }
    }
}
//bufind is the next slot
void flush_codes(int outfile) { //Write out any leftover buffered bits.
    uint32_t amount = 0;

    if (bufind > 0) {
        //convert num of bits in the buffer to least num of bytes possible
        if (bufind % 8 > 0) {
            amount = 1;
        }
        amount += bufind;
        //Zero out some bits

        for (uint32_t i = bufind; i < amount; i++) { //For loop to zero out the bits
            buf[i / 8] &= ~(0x1 << (i % 8));
        }
        write_bytes(outfile, buf, amount);
    }
}

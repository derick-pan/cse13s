//Derick Pan
//dpan7
//io.c
#include "io.h"

#include "code.h"

#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
uint64_t bytes_read = 0;
uint64_t bytes_written = 0;

static uint8_t buf[BLOCK];
static int bufind = 0;

//Wrapper function to read()
int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int bytes = 0; //Number of bytes read with each read
    int localbytes = 0; //Number of bytes read total in current call
    while ((bytes = read(infile, buf, nbytes)) > 0) {
        buf += bytes; //Increase position of buffer
        bytes_read += bytes; //Increase total bytes read
        nbytes -= bytes; //Decrease bytes still need to be read
        localbytes += bytes; //Increase bytes just read
    }
    return localbytes; //Return number of bytes just read
}

//Wrapper function to write()
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bytes = 0; //Number of bytes written in one write
    int localbytes = 0; //Number of bytes read total in current call
    while ((bytes = write(outfile, buf, nbytes)) > 0) {
        buf += bytes; //Increase position of buffer
        bytes_written += bytes; //Increase total bytes written
        localbytes += bytes; //Decrease bytes still need to be written
        nbytes -= bytes; //Increase bytes just written
    }
    return localbytes; //Return number of bytes just written
}

// Function that doles out bits read one at a time
bool read_bit(int infile, uint8_t *bit) {

    // If buffer is full    or buffer is empty
    if (bufind == BLOCK * 8 || bufind == 0) {

        if (read_bytes(infile, buf, BLOCK) <= 0) { //If file is readable
            bufind = 0; //Reset index
            return false; // return false
        }
        bufind = 0;
    }
    //pass back bit at bufind through pointer
    *bit = (buf[bufind / 8] >> (bufind % 8) & 0x1); //Get the bit
    bufind += 1;
    return true;
}

// Function to write out codes
//Code is based off of Euguene's Pseudocode
void write_code(int outfile, Code *c) { //calls write bytes , used in main
    //Each bit in the code c is buffered into the buffer
    //Create a loop to iterate over the buffer
    for (uint32_t i = 0; i < c->top; i++) {

        if ((c->bits[i / 8] >> (i % 8) & 0x1) == 1) { //If bit is a 1
            //Set the bit to 1 at buffer
            buf[bufind / 8] |= 0x1 << (bufind % 8);
        } else {
            //Set the bit to 0 at the buffer location
            buf[bufind / 8] &= ~(0x1 << (bufind % 8));
        }
        bufind += 1;

        //If the Buffer is full, write it!
        if (bufind == BLOCK * 8) {
            write_bytes(outfile, buf, BLOCK);
            bufind = 0;
        }
    }
}

//Writes out the code if the buffer isn't size of BLOCk
void flush_codes(int outfile) { //Write out any leftover buffered bits.
    uint32_t amount = bufind; // Amount of bits to write
    if (bufind % 8 != 0) {
        amount += 8 - (bufind % 8); //In bits
        for (uint32_t i = bufind; i <= amount; i++) { //For loop to zero out the bits till next byte
            buf[i / 8] &= ~(0x1 << (i % 8));
        }
        write_bytes(outfile, buf, amount / 8 +1);
    }
    printf("Flush code buffer index: %u \n", bufind);
}

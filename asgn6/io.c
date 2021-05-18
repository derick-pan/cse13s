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
//extern uint64_t bytes_read;
//extern uint64_t bytes_written;
//Block = 4096
static uint8_t buf[BLOCK]; //Declare buffer in io.c //4096 items of uint8_t's
static int bufind = 0; //Declare buffer index

int read_bytes(int infile, uint8_t *buf, int nbytes) { //Internal function
    int bytes = 0; //Number of bytes read
    int localbytes = 0;
    while ((bytes = read(infile, buf, nbytes)) > 0) {
        buf += bytes; //Increase position of buffer
        bytes_read += bytes;
        nbytes -= bytes;
        localbytes += bytes;
    }
    return localbytes;
}

//Internal Function
int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int bytes = 0; //Number of bytes written in one write
    int localbytes = 0;
    while ((bytes = write(outfile, buf, nbytes)) > 0 /* && (int) bytes_written != nbytes*/) {
        buf += bytes; //Increase position of buffer
        bytes_written += bytes;
        localbytes += bytes;
        nbytes -= bytes;
    }
    return localbytes;
}

//External Function
bool read_bit(int infile, uint8_t *bit) { //Calls read_bytes, used in main
    //Uses functionality of read_bytes
    //if buffer empty or the buffer's index is the size of a block

    // If buffer is full    or buffer is empty
    if (bufind == BLOCK * 8 || bufind == 0) {

        if (read_bytes(infile, buf, BLOCK) <= 0) { // If I can read
            bufind = 0; //Reset index
            return false; // return false
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
    //printf("Bufind: %u\n", bufind);
    //bufind = 0;
    //Each bit in the code c is buffered into the buffer
    //Create a loop to iterate over the buffer

    //Code is based off of Euguene's Pseudocode

    for (uint32_t i = 0; i < c->top; i++) {

        if ((c->bits[i / 8] >> (i % 8) & 0x1) == 1) { //If this bit is a 1
            //Set the bit to 1 at buffer
            buf[bufind / 8] |= 0x1 << (bufind % 8);
        } else {
            //Set the bit to 0 at the buffer location
            buf[bufind / 8] &= ~(0x1 << (bufind % 8));
        }

        bufind += 1;

        //buffind is in bits, block in bytes
        if (bufind == BLOCK * 8) {
            //Fill the buffer if fillable
            printf("Should not be in here");
            write_bytes(outfile, buf, BLOCK);
            bufind = 0;
        }
    }
    //printf("¯_(ツ)_/¯ \n");
}

//bufind is the next slot
void flush_codes(int outfile) { //Write out any leftover buffered bits.
    printf("\n bufind: %u\n", bufind);
    uint32_t amount = bufind;
    //ex.
    //250 bits left in buffer . I need minimum 256/8 bits =32 bytes
    if (bufind % 8 != 0) {
        amount += 8 - (bufind % 8); //In bits
        for (uint32_t i = bufind; i < amount; i++) { //For loop to zero out the bits till next byte
            buf[i / 8] &= ~(0x1 << (i % 8));
        }
        //printf("buffer0: %u \n",buf[0]);
        //printf("buffer1: %u \n",buf[1]);
        write_bytes(outfile, buf, amount / 8);
    }
}

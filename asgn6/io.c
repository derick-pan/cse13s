//Derick Pan
//dpan7
//io.c
#include "io.h"

#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern uint64_t bytes_read;
extern uint64_t bytes_written;

int buf[BLOCK]; //Declare buffer in io.c

int read_bytes(int infile, uint8_t *buf, int nbytes) { //Internal function
    uint64_t bytes_read; //Total num of bytes read from infile
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
    int bytes_written; //Total num of bytes written to outfile
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
}

//External Function
void write_code(int outfile, Code *c); //calls write bytes , used in main

void flush_codes(int outfile);

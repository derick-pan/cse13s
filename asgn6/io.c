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

int read_bytes(int infile, uint8_t *buf, int nbytes) {
    int counter = 0; //Total num of bytes read from infile
    int bytes; //Number of bytes read
    // -1,0 is the error return , so set it greater than 0
    while ((bytes = read(infile, buf, nbytes)) > 0 && counter != nbytes) {
        buf += bytes; //Increase position of buffer
        counter += bytes;
    }
    return counter;
}

int write_bytes(int outfile, uint8_t *buf, int nbytes) {
    int counter = 0; //Total num of bytes written to outfile
    int bytes; //Number of bytes written in one write
    // -1,0 is the error return , so set it greater than 0
    while ((bytes = write(outfile, buf, nbytes)) > 0 && counter != nbytes) {
        buf += bytes; //Increase position of buffer
        counter += bytes;
    }
    return counter;
}

bool read_bit(int infile, uint8_t *bit);

void write_code(int outfile, Code *c);

void flush_codes(int outfile);

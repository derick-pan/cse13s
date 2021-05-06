//Derick Pan
//dpan7
//Asgn5
//Decode.c
#include "bm.h"
#include "bv.h"
#include "hamming.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char usage[1000] = "SYNOPSIS\n\
  A Hamming(8, 4) systematic code decoder.\n\n\
USAGE\n\
  ./decode [-h] [-v] [-i infile] [-o outfile]\n\n\
OPTIONS\n\
  -h             Program usage and help.\n\
  -v             Print statistics of decoding to stderr.\n\
  -i infile      Input data to decode.\n\
  -o outfile     Output of decoded data.\n";

uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}
// Returns the upper nibble of val
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}
// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

int main(int argc, char *argv[]) {
    int choice;
    //bool sdout = false;
    char infile[20]; //Read the file input from user
    char fileout[100]; //File output for user
    FILE *stdin;
    FILE *outfile;
    outfile = stdout;
    while ((choice = getopt(argc, argv, "hvi:o:")) != -1) {
        switch (choice) {
        case 'h': fprintf(stderr, "%s", usage); exit(0); // Print helps
        case 'v': break; //Print stats of decoding
        case 'i':
            if (optarg != NULL) { //If argument isn't null
                //printf("sad1\n");
                snprintf(infile, 20, "%s", optarg);
                //printf("sad2\n");
                stdin = fopen(optarg, "r");
                //printf("sad3\n");
                if (access(infile, R_OK) != 0) { // if file exists
                    fprintf(stderr, "Error: failed to open infile.\n");
                    exit(0);
                }
            }
            break;
        case 'o':
            if (optarg != NULL) {
                snprintf(fileout, 20, "%s", optarg);
                outfile = fopen(optarg, "w");
                break;
            }
            fprintf(stderr, "Error: failed to open infile.\n");
            exit(0);

        case '?': fprintf(stderr, "%s", usage); exit(0);
        }
    }
    struct stat statbuf;
    fstat(fileno(stdin), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    //Create the transposed Matrix
    BitMatrix *Ht = bm_create(8, 4);
    for (uint8_t i = 4; i < 8; i++) { //Columns
        for (uint8_t j = 0; j < 4; j++) { //Rows
            if (j + 4 == i) {
                bm_set_bit(Ht, i, j);
            }
        }
    }
    for (uint8_t i = 0; i < 4; i++) { //Columns
        for (uint8_t j = 0; j < 4; j++) { //Rows
            if (i != j) {
                bm_set_bit(Ht, j, i);
            }
        }
    }

    bm_print(Ht);
    uint8_t msg1;
    uint8_t msg2;
    choice = 0;
    int choice2;
    while ((choice = fgetc(stdin)) != EOF) { //Every Byte is a code
        //We need two codes to convert back to a singular byte of data

        choice2 = fgetc(stdin);
        //printf("%d , %d \n", choice,choice2);
        ham_decode(Ht, choice, &msg1); //Read in first Code || Hamming code for lower nibble
        ham_decode(Ht, choice2, &msg2); //Read in second code || Hamming code for upper nibble
        //printf("%u  , %u \n", msg1,msg2);
        //fputc(pack_byte(lower_nibble(msg1),upper_nibble(msg2) ), outfile);
        //fputc(pack_byte(upper_nibble(msg2), lower_nibble(msg1)), outfile);
        fputc(pack_byte(lower_nibble(msg2), lower_nibble(msg1)), outfile);
        //fputc(pack_byte(msg2, msg1), outfile);
    }
    fclose(stdin);
    fclose(outfile);
    bm_delete(&Ht);
}

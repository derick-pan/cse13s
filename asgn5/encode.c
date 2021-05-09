//Derick Pan
//dpan7
//Asgn5
//Encode.c
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
  A Hamming(8, 4) systematic code generator.\n\n\
USAGE\n\
  ./encode [-h] [-i infile] [-o outfile]\n\n\
OPTIONS\n\
  -h             Program usage and help.\n\
  -i infile      Input data to encode.\n\
  -o outfile     Output of encoded data.\n\
";

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
    FILE *filein;
    filein = stdin;
    FILE *outfile;
    outfile = stdout;
    while ((choice = getopt(argc, argv, "hi:o:")) != -1) {
        switch (choice) {
        case 'h': fprintf(stderr, "%s", usage); exit(1); // Print helps
        case 'i':
            if (optarg != NULL) { //If argument isn't null
                if ((filein = fopen(optarg, "r")) == NULL) {
                    fprintf(stderr, "Error: failed to open %s.\n", optarg);
                    exit(1);
                }
            }
            break;
        case 'o':
            if (optarg != NULL) {
                outfile = fopen(optarg, "w");
                break;
            }
            fprintf(stderr, "Error: failed to open infile.\n");
            exit(1);
        case '?': fprintf(stderr, "%s", usage); exit(1);
        }
    }
    struct stat statbuf;
    fstat(fileno(filein), &statbuf);
    fchmod(fileno(outfile), statbuf.st_mode);

    /* ########## CREATE AUGMENTED MATRIX ########### */
    BitMatrix *G = bm_create(4, 8);
    for (uint8_t k = 0; k < 4; k++) { //Left side Diagonal
        bm_set_bit(G, k, k);
    }
    for (uint8_t j = 0; j < 4; j++) { //Rows
        for (uint8_t i = 4; i < 8; i++) { //Columns
            if (i != j + 4) {
                bm_set_bit(G, j, i);
            }
        }
    }
    /* ######### FINISH AUGMENTED MATRIX ############ */

    int read;
    while ((read = fgetc(filein)) != EOF) { //Every byte we read becomes two message bits
        fputc(ham_encode(G, lower_nibble(read)), outfile); //Pass lower nibble
        fputc(ham_encode(G, upper_nibble(read)), outfile); //Pass Upper nibble
    }
    fclose(filein);
    fclose(outfile);
    bm_delete(&G);
}

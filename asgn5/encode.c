//Derick Pan
//dpan7
//Asgn5
//Encode.c
#include "bm.h"
#include "bv.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
char usage[1000] = "SYNOPSIS\n\
  A Hamming(8, 4) systematic code generator.\n\n\
USAGE\n\
  ./encode [-h] [-i infile] [-o outfile]\n\n\
OPTIONS\n\
  -h             Program usage and help.\n\
  -i infile      Input data to encode.\n\
  -o outfile     Output of encoded data.\n\
";

int main(int argc, char *argv[]) {
    int choice;
    //bool sdout = false;
    char infile[20]; //Read the file input from user
    char fileout[100]; //File output for user

    while ((choice = getopt(argc, argv, "hi:o:")) != -1) {
        switch (choice) {
        case 'h': fprintf(stderr, "%s", usage); exit(0); // Print helps

        case 'i':
            if (optarg != NULL) { //If argument isn't null
                snprintf(infile, 20, "%s", optarg);
                if (access(infile, R_OK) != 0) { // if file exists
                    fprintf(stderr, "Error: failed to open infile.\n");
                    exit(0);
                }
            }
            break;
        case 'o':
            if (optarg != NULL) {
                snprintf(fileout, 20, "%s", optarg);
                //sdout = true;
                break;
            } else {
                fprintf(stderr, "%s", usage);
            }
            exit(0);
        case '?': fprintf(stderr, "%s", usage); exit(0);
        }
    }

    // Opening files to read and write to
    FILE *stdin = fopen(infile, "rb");
    FILE *outfile = fopen(fileout, "wb");

    // Getting and setting file permissions
    struct stat statbuf ;
    fstat ( fileno ( stdin ) , & statbuf ) ;
    fchmod ( fileno ( outfile ) , statbuf . st_mode ) ;

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

    bm_print(G);

    char c = fgetc(stdin);
    printf("first char: %c\n",c);

}

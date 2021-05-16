//Derick Pan
//dpan7
//encode.c

#include "code.h"
#include "defines.h"
#include "huffman.h"
#include "io.h"
#include "node.h"
#include "pq.h"
#include "stack.h"

#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char usage[1000] = "SYNOPSIS\n\
  A Huffman encoder.\n\
  Compresses a file using the Huffman coding algorithm.\n\n\
USAGE\n\
  ./encode [-h] [-i infile] [-o outfile]\n\n\
OPTIONS\n\
  -h             Program usage and help.\n\
  -v             Print compression statistics.\n\
  -i infile      Input file to compress.\n\
  -o outfile     Output of compressed data.\n";

int main(int argc, char *argv[]) {
    int choice;
    bool stats = false;
    int infile = 0; //File descriptor for stdin is 0
    int outfile = 1; //File descriptor for stdout is 1
    while ((choice = getopt(argc, argv, "hvi:o:")) != -1) {
        switch (choice) {
        case 'h': fprintf(stderr, "%s", usage); exit(0); // Print helps
        case 'v': stats = true; break; //Print stats of decoding
        case 'i':
            if (optarg != NULL) { //If argument isn't null
                if ((infile = open(optarg, O_RDONLY)) == -1) {
                    fprintf(stderr, "Error: failed to open %s.\n", optarg);
                    exit(1);
                }
            }
            break;
        case 'o':
            if (optarg != NULL) {
                outfile = open(optarg, O_WRONLY | O_CREAT | O_TRUNC, 0600);
                break;
            }
            fprintf(stderr, "Error: failed to open infile.\n");
            exit(1);
        case '?': fprintf(stderr, "%s", usage); exit(1);
        }
    }

    //########## Construct HISTOGRAM ###########
    //256 index, each index has 64 bits
    uint64_t hist[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) {
        hist[i] = 0;
    }

    uint8_t readingbuff;
    uint8_t temp = 0;
    uint8_t counter = 0;
    while (read_bit(infile, &readingbuff)) {
        if (readingbuff == 1) { //If this bit is a 1
            //Set the bit to 1 at buffer
            temp |= 0x1 << counter;
        } else {
            //Set the bit to 0 at the buffer location
            temp &= ~(0x1 << counter);
        }

        counter += 1;
        if (counter % 8 == 0 && temp > 0) {
            counter = 0;
            hist[temp] += 1; // MAY NOT BE THIS? BUT SHOULD BE
            printf("Ascii and index: %u  frequency: %" PRIu64 "\n", temp, hist[temp]);
        }
    }
    hist[0] += 1; //Min of 2 elements
    hist[255] += 1;

    //Calculate How many Unique symbols:
    int uniquesym = 0;
    for (int i = 0; i < 20; i++) {
        if (hist[i] > 0) {
            uniquesym += 1;
        }
    }

    Node root = *build_tree(hist);

    Code c[ALPHABET];

    build_codes(&root, c); //ur problematic

    printf("Back at main:\n");
    code_print(&c[97]);
    for (int i = 0; i < ALPHABET; i++) {
        code_print(&c[i]);
    }

    printf("end here");
    exit(1);
    //printf("crash here");

    typedef struct Header {
        uint32_t magic;
        uint16_t permissions;
        uint16_t tree_size;
        uint64_t file_size;
    } Header;
    struct stat statbuf;
    Header myheader;
    myheader.magic = MAGIC;
    myheader.permissions = fstat(infile, &statbuf);
    fchmod(outfile, statbuf.st_mode);
    myheader.tree_size = (3 * uniquesym) - 1;
    myheader.file_size = statbuf.st_size;

    //Write the header to outfile

    //Create the dump
}

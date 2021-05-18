//Derick Pan
//dpan7
//decode.c

#include "code.h"
#include "defines.h"
#include "header.h"
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
  A Huffman decoder.\n\
  Decompresses a file using the Huffman coding algorithm.\n\n\
USAGE\n\
  ./decode [-h] [-i infile] [-o outfile]\n\n\
OPTIONS\n\
  -h             Program usage and help.\n\
  -v             Print compression statistics.\n\
  -i infile      Input file to decompress.\n\
  -o outfile     Output of decompressed data.\n";

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

    /* ################## Step 1&2 #################  */
                   //Check magic number


    uint8_t readingbuff[sizeof(Header)]; // Buffer for bytes while reading.
    Header myheader;
    uint32_t magictest=0x00000000;
    //uint8_t treedump[BLOCK];

    read_bytes(infile, readingbuff, 4); // Testing Magic Number
    for (int i =3; i >=0; i--){
        magictest <<= 8;
        magictest |= readingbuff[i];
    }
    if (magictest !=MAGIC){
        printf("Invalid Magic Number.\n");
        exit(1);
    }

    uint8_t temp;
    int counter = 0;
    while (read_bit(infile, &temp)) {
        if (counter<16){
            myheader.permissions <<= 1;
            myheader.permissions |= temp;
        }
        else if (counter< 32){
            myheader.tree_size <<= 1;
            myheader.tree_size |= temp;
        }
        else if (counter > 96) {
            myheader.file_size <<= 1;
            myheader.file_size |= temp;
        }
        else{
            break;
        }
        counter++;
    }
    fchmod(outfile, myheader.permissions); //Set perms of outfile

    printf("Permissions: %u , Tree_size %u , File Size: %" PRIu64 "\n" , myheader.permissions, myheader.tree_size, myheader.file_size);

    //if (magictest != MAGIC){
        //printf("Magicnum: %x \n", magictest);
        //printf("Invalid magic number.\n");
//    }


    //Node *root = rebuild_tree(tree_size, treedump);

    //while (read_bit)



    /* ### Free leftover memory ### */
    close(infile);
    close(outfile);
}

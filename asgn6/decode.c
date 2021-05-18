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
    //  read_bytes(infile, &readingbuff, 4);

    uint8_t readingbuff[sizeof(Header)]; // Buffer for bytes while reading.
    Header myheader;
    uint32_t magictest = 0x00000000;

    read_bytes(infile, readingbuff, sizeof(Header));

    for (int i = 3; i >= 0; i--) { // Testing Magic Number
        magictest <<= 8;
        magictest |= readingbuff[i];
    }
    if (magictest != MAGIC) {
        printf("Invalid Magic Number.\n");
        exit(1);
    }

    for (int i = 5; i >= 4; i--) {
        myheader.permissions <<= 8;
        myheader.permissions |= readingbuff[i];
    }
    for (int i = 7; i >= 6; i--) {
        myheader.tree_size <<= 8;
        myheader.tree_size |= readingbuff[i];
    }
    for (int i = 15; i >= 8; i--) {
        myheader.file_size <<= 8;
        myheader.file_size |= readingbuff[i];
    }

    // Perms, Perms, Tree, Tree, File, file,
    printf("\n");

    printf("Permissions: %u , Tree_size %u , File Size: %" PRIu64 "\n", myheader.permissions,
        myheader.tree_size, myheader.file_size);

    uint8_t temp;
    uint8_t tree[myheader.tree_size];

    for (uint8_t i = 0; i < myheader.tree_size; i++) {
        read_bytes(infile, &temp, 1);
        tree[i] = temp;
        printf("%c ", tree[i]);
    }

    //printf("\nWe seg fauly here HELLO123OOO\n\n\n");
    Node *root = rebuild_tree(myheader.tree_size, tree);

    //node_print(root);

    uint16_t decodedsym = 0;
    Node *walk = root;
    uint8_t writeout[myheader.file_size];

    while (decodedsym != myheader.file_size && read_bit(infile, &temp)) {
        //printf("nothing?? %u\n\n", temp);
        if (temp == 0) {
            //Walk down to left child
            walk = walk->left;
        } else {
            //Walk down to right
            walk = walk->right;
        }
        if (walk->left == NULL && walk->left == NULL) {
            writeout[decodedsym] = walk->symbol;
            decodedsym += 1;
            walk = root;
        }
    }
    printf("decoded sym: %u\n", decodedsym);

    for (uint8_t i = 0; i < myheader.file_size; i++) {
        printf("%c ", writeout[i]);
    }
    printf("um\n");
    write_bytes(outfile, writeout, (int) decodedsym);

    /* ### Free leftover memory ### */
    close(infile);
    close(outfile);
}

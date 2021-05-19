//Derick Pan
//dpan7
//encode.c
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
  A Huffman encoder.\n\
  Compresses a file using the Huffman coding algorithm.\n\n\
USAGE\n\
  ./encode [-h] [-i infile] [-o outfile]\n\n\
OPTIONS\n\
  -h             Program usage and help.\n\
  -v             Print compression statistics.\n\
  -i infile      Input file to compress.\n\
  -o outfile     Output of compressed data.\n";

void post_traversal(Node *root, int outfile) {

    if (root->left == NULL && root->left == NULL) {
        uint8_t out[2]; //Ascii code for leaf
        out[0] = 'L';
        out[1] = root->symbol;
        write_bytes(outfile, out, 2);
        return;
    } else { //Must be an interior node
        post_traversal(root->left, outfile); // RECURSE to left link
        post_traversal(root->right, outfile); // RECURSE to right
        uint8_t i = 'I';
        write_bytes(outfile, &i, 1);
    }
}

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
    /* Read through infile to construct histogram     */

    uint8_t readingbuff; // Buffer for bytes while reading

    if (infile == 0) { //If input is stdin then I will create a temporary file
        int path = creat("t3mp0r6rY_hOIdlng_fi1e", S_IRWXU);
        while (read_bytes(infile, &readingbuff, 1) > 0) { //Write stdin into file
            write_bytes(path, &readingbuff, 1);
        }
        close(infile);
        infile = open("t3mp0r6rY_hOIdlng_fi1e", O_RDONLY);
    }

    uint64_t hist[ALPHABET]; // Histogram
    int uniquesym = 2; // Unique Symbols counter;

    for (int i = 0; i < ALPHABET; i++) { //Clear the bits in histogram
        hist[i] = 0;
    }

    while (read_bytes(infile, &readingbuff, 1) > 0) {
        hist[readingbuff] += 1; //Increment position in histogram
        if (hist[readingbuff] == 1) {
            uniquesym += 1; //Unique symbols counter
        }
    }
    /* Increment the two counts for handling specific cases */
    hist[0] += 1, hist[255] += 1;

    /* ################## Step 3. ################## */
    /* Construct the Huffman Tree using build_tree   */
    Node *root = build_tree(hist);

    /* ################## Step 4. ################## */
    /* Construct a code table by using build_codes   */
    Code c[ALPHABET];
    for (int i = 0; i < ALPHABET; i++) { // Initalize all of the codes
        if (hist[i] > 0) {
            c[i] = code_init();
        }
    }
    build_codes(root, c);

    /* ################ Step 5 & 6 ################# */
    /*          Construct and write a header         */
    /*
        Terms in header
        magic          Identifies this file as compressed
        permissions    Input File Permissions
        tree_size      Tree size in bytes
        file_size      File size of Input
    */
    struct stat statbuf;
    Header myheader;
    myheader.magic = MAGIC; // Identifies this file as compressed
    fstat(infile, &statbuf);
    myheader.permissions = statbuf.st_mode;
    fchmod(outfile, statbuf.st_mode); //Set perms of outfile
    myheader.tree_size = (3 * uniquesym) - 1;
    myheader.file_size = statbuf.st_size;
    write(outfile, &myheader, sizeof(myheader));

    /* ################## Step 7. ################## */
    /*              Create the tree dump             */
    post_traversal(root, outfile);

    /* ################## Step 8. ################## */
    /*            Write corresponding codes          */

    lseek(infile, 0, SEEK_SET); // Reset pointer of read to beginning

    while (read_bytes(infile, &readingbuff, 1) > 0) {
        write_code(outfile, &c[readingbuff]);
    }
    flush_codes(outfile);

    /* ### Free leftover memory ### */
    delete_tree(&root);

    close(infile);
    close(outfile);
}

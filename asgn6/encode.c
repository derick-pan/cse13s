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
#include <math.h>
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

//Creating Tree Dump should work Fine
void post_traversal(Node *root, int outfile) {
    if (NULL == root->left && NULL == root->right) {
        uint8_t out[2]; //Ascii code for leaf
        out[0] = 'L';
        out[1] = root->symbol;
        write_bytes(outfile, out, 2);
        return;
    } else { //Must be an interior node
        uint8_t i = 'I';
        post_traversal(root->left, outfile); // RECURSE to left link
        post_traversal(root->right, outfile); // RECURSE to right
        write_bytes(outfile, &i, 1);
    }
}
uint64_t bytes_written;
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
                outfile = open(optarg, O_WRONLY | O_CREAT);
                break;
            }
            fprintf(stderr, "Error: failed to open infile.\n");
            exit(1);
        case '?': fprintf(stderr, "%s", usage); exit(1);
        }
    }

    /* If user supplied No file and wants stdin to be encoded then this if
    statement will execute, creating a temporary file and deleting it later on.*/

    uint8_t readingbuff; // Buffer for bytes while reading
    uint8_t transferring[BLOCK]; // A second Buffer with Size of Block.
    if (infile == 0) { //If input is stdin then I will create a temporary file
        uint16_t bufinda = 0;
        //Temporary file has a unique name as to have an incredibly low chance of
        //user having the exact same file name.
        int path = creat("t3mp0r6rY_hOIdlng_fi1e", S_IRWXU);
        while (read_bytes(infile, &readingbuff, 1) > 0) { //Write stdin into file
            transferring[bufinda] = readingbuff;
            bufinda += 1;
            //If bufind size of block then write_bytes
            if (bufinda == BLOCK) {
                write_bytes(path, transferring, BLOCK);
                bufinda = 0;
            }
        }
        if (bufinda != 0) { //Flush out the write_bytes if any remaining
            write_bytes(path, transferring, bufinda);
        }
        infile = open("t3mp0r6rY_hOIdlng_fi1e", O_RDONLY);
        bytes_written = 0;
    }

    /* ################## Step 1&2 #################  */
    /* Read through infile to construct histogram     */
    uint64_t hist[ALPHABET]; // Histogram
    int uniquesym = 2; // Unique Symbols counter;
    for (int i = 0; i < ALPHABET; i++) { //Clear the bits in histogram
        hist[i] = 0;
    }

    while (read_bytes(infile, &readingbuff, 1) > 0) { //Generate Histogram
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

    for (int i = 0; i < ALPHABET; i++) { // Initalize ONLY positions to be used
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
        file_size      File size of Input            */
    bytes_written = 0;
    struct stat statbuf;
    Header myheader; // Create the Header
    myheader.magic = MAGIC; // Identifies this file as compressed
    fstat(infile, &statbuf); // Grab the stats of infile
    myheader.permissions = statbuf.st_mode; //Copy the permissions
    fchmod(outfile, statbuf.st_mode); //Set perms of outfile
    myheader.tree_size = (3 * uniquesym) - 1; //Get the size of the Tree
    myheader.file_size = statbuf.st_size; //Get the file size

    write_bytes(outfile, (uint8_t *) &myheader, sizeof(Header)); // Write Header to outfile


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

    /* If the user wants statistics then we print out the stats. */
    if (stats == true) {
        double spacesave = (100 * (1 - ((double) bytes_written / myheader.file_size)));
        fprintf(stderr, "Uncompressed file size: %lu bytes\n\
Compressed file size: %lu bytes\n\
Space saving: %.2lf%%\n",
            myheader.file_size, bytes_written, spacesave);
    }

    /* ### Free leftover memory ### */
    delete_tree(&root);
    close(infile);
    remove("t3mp0r6rY_hOId0Ut_fi1e");
    remove("t3mp0r6rY_hOIdlng_fi1e");
    close(outfile);
}

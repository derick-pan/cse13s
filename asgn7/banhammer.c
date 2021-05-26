//Derick Pan
//dpan7
//banhammer
#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

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

#define WORD "[a-zA-Z]+"

char usage[1000] = "SYNOPSIS\n\
  A word filtering program for the GPRSC.\n\
  Filters out and reports bad words parsed from stdin.\n\n\
USAGE\n\
  ./banhammer [-hsm] [-t size] [-f size]\n\n\
OPTIONS\n\
  -h           Program usage and help.\n\
  -s           Print program statistics.\n\
  -m           Enable move-to-front rule.\n\
  -t size      Specify hash table size (default: 10000).\n\
  -f size      Specify Bloom filter size (default: 2^20).\n";

int main(int argc, char *argv[]) {
    int choice;
    bool stats = false;
    uint32_t hashsize = 10000; // Default hash table size is 10,000
    uint32_t bloomsize = 1048576; // Default Bloom filter size
    bool mtf = false;
    while ((choice = getopt(argc, argv, "hsmt:f:")) != -1) {
        switch (choice) {
        case 'h': fprintf(stderr, "%s", usage); exit(0); // Print helps
        case 's': stats = true; break; //Print stats of decoding
        case 'm': mtf = true; break; // Move to front rule true
        case 't':
            if (optarg != NULL) {
                hashsize = (uint32_t) optarg;
                break;
            }

            exit(1);
        case 'f':
            if (optarg != NULL) {
                bloomsize = (uint32_t) optarg;
                break;
            }
            exit(1);
        case '?': fprintf(stderr, "%s", usage); exit(1);
        }
    }
    // Part 1: Read in a list of badspeak words and add it to bloomfilter& HashTable
    char buffer[100];
    printf("heyy1\n");
    BloomFilter *bf = bf_create(bloomsize);
    HashTable *ht = ht_create(hashsize, mtf);

    printf("heyy3\n");
    FILE *badspeaktxt = fopen("badspeak.txt", "r");
    while (fscanf(badspeaktxt, "%[^\n] ", buffer) != EOF) {
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, NULL);
    }
    // Part 2: Read newspeak. Add old to bf, and old & new to hash
    fclose(badspeaktxt);
    printf("Read badspeak.txt, now reading newspeak.txt\n");

    char *old;
    char *new;
    FILE *newspeaktxt = fopen("newspeak.txt", "r");
    while (fscanf(newspeaktxt, "%[^\n] ", buffer) != EOF) {
        old = strtok(buffer, " ");
        bf_insert(bf, old);
        new = strtok(NULL, " ");
        ht_insert(ht, old, new);
    }
    regex_t reg;
    char *word = NULL;

    if (regcomp(&reg, WORD, REG_EXTENDED) != 0) {
        fprintf(stderr, "failed");
        exit(1);
    }

    LinkedList *badwords = ll_create(false);
    LinkedList *oldwords = ll_create(false);

    Node *node;
    while ((word = next_word(stdin, &reg)) != NULL) {
        printf("Word : %s \n", word);

        if (bf_probe(bf, word) == false) { //If word is already in bf: continue
            continue;
        } else {
            if ((node = ht_lookup(ht, word)) == NULL) {
                //If hashtable does not have word
                //No action is taken
                continue;
            } else if (node->newspeak == NULL) {
                //If node has NO newspeak translation
                //Insert badspeak word into a badspeak LIST
                printf("\t\t1a\n");
                ll_insert(badwords, word, NULL);
                printf("\t\t2a\n");
            } else if (node->newspeak != NULL) {
                //If node HAS newspeak translation
                //Insert oldspeak word into oldspeak list
                printf("\t\t1b\n");
                ll_insert(oldwords, word, node->newspeak);
                printf("\t\t2b\n");
            }
        }
    }
}

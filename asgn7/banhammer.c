//Derick Pan
//dpan7
//banhammer
#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "messages.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <fcntl.h>
#include <inttypes.h>
#include <math.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define WORD "([a-zA-Z0-9]+)|([a-zA-Z0-9]+(['--]?[a-zA-Z0-9]+)*)"
uint64_t seeks = 0; // Number of seeks performed.
uint64_t links = 0; // Number of links traversed.
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
    BloomFilter *bf = bf_create(bloomsize);
    HashTable *ht = ht_create(hashsize, mtf);

    FILE *badspeaktxt = fopen("badspeak.txt", "r");
    while (fscanf(badspeaktxt, "%[^\n] ", buffer) != EOF) {
        bf_insert(bf, buffer);
        ht_insert(ht, buffer, NULL);
    }
    fclose(badspeaktxt);

    // Part 2: Read newspeak. Add old to bf, and old & new to hash
    char old[100];
    char new[100];
    FILE *newspeaktxt = fopen("newspeak.txt", "r");
    while (fscanf(newspeaktxt, "%s %s", old, new) != EOF) {
        bf_insert(bf, old);
        ht_insert(ht, old, new);
    }
    fclose(newspeaktxt);

    //Read words from stdin using the parsing module.
    regex_t reg;
    char *word = NULL;
    if (regcomp(&reg, WORD, REG_EXTENDED)) {
        fprintf(stderr, "failed\n");
        exit(1);
    }
    LinkedList *badwords = ll_create(mtf);
    LinkedList *oldwords = ll_create(mtf);

    Node *node;
    while ((word = next_word(stdin, &reg)) != NULL) {
        for (uint32_t i = 0; word[i]; i++) {
            word[i] = tolower(word[i]);
        }
        if (bf_probe(bf, word) == false) { //If word is already in bf: continue
            continue;
        } else {
            if ((node = ht_lookup(ht, word)) == NULL) {
                continue;
            } else if (node->newspeak == NULL) {
                ll_insert(badwords, word, NULL);
            } else if (node->newspeak != NULL) {
                ll_insert(oldwords, word, node->newspeak);
            }
        }
    }
    uint32_t badwordlen = ll_length(badwords);
    uint32_t oldwordlen = ll_length(oldwords);
    if (stats == true) {
        printf("Seeks: %lu\n", seeks);
        printf("Average seek length: %f\n", (double) links / seeks);
        printf("Hash table load: %f%%\n", (double) 100 * ht_count(ht) / ht_size(ht));
        printf("Bloom filter load: %f%%\n", (double) 100 * bf_count(bf) / bf_size(bf));
    }
    //Citizen is accused of thoughtcrime & requires counseling on rightspeak
    //I give them a reprimanding mixspeak message.
    else if (badwordlen > 0 && oldwordlen > 0) {
        printf("%s", mixspeak_message);
        ll_print(badwords);
        ll_print(oldwords);
    }
    // Citizen is solely accused of thoughtcrime. We give a badspeak message.
    else if (badwordlen > 0 && oldwordlen == 0) {
        printf("%s", badspeak_message);
        ll_print(badwords);
    }
    // Citizen only requires counseling to correct wrongthink
    else if (badwordlen == 0 && oldwordlen > 0) {
        printf("%s", goodspeak_message);
        ll_print(oldwords);
    }

    regfree(&reg);
    ht_delete(&ht);
    printf("Here1?\n");
    bf_delete(&bf);
    printf("Here2?\n");
    ll_delete(&badwords);
    printf("Here3?\n");
    ll_delete(&oldwords);
    printf("Here4?\n");
}

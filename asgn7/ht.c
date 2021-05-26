//Derick Pan
//dpan7
//ht.c
#include "ht.h"

#include "bf.h"
#include "bv.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct HashTable {
    uint64_t salt[2];
    uint32_t size;
    bool mtf;
    LinkedList **lists;
} HashTable;

HashTable *ht_create(uint32_t size, bool mtf) {
    HashTable *ht = (HashTable *) malloc(sizeof(HashTable));
    if (ht) {
        // Leviathan
        ht->salt[0] = 0x9846e4f157fe8840;
        ht->salt[1] = 0xc5f318d7e055afb8;
        ht->size = size;
        ht->mtf = mtf;
        ht->lists = (LinkedList **) calloc(size, sizeof(LinkedList *));
        if (!ht->lists) {
            free(ht);
            ht = NULL;
        }
    }
    return ht;
}

//Each of the linked lists in lists is freed
void ht_delete(HashTable **ht) {
    if (*ht) {
        for (uint32_t i = 0; i < (*ht)->size; i++) {
            free((*ht)->lists[i]);
        }
        free(*ht);
        *ht = NULL;
    }
}

uint32_t ht_size(HashTable *ht) {
    return ht->size;
}

//Search for a node that contains oldspeak
Node *ht_lookup(HashTable *ht, char *oldspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    return ll_lookup(ht->lists[index], oldspeak);
}

void ht_insert(HashTable *ht, char *oldspeak, char *newspeak) {
    uint32_t index = hash(ht->salt, oldspeak) % ht->size;
    //if not initialized then create it
    if (!ht->lists[index]) {
        ht->lists[index] = ll_create(ht->mtf);
    }
    //printf("Crash before insert\n");
    ll_insert(ht->lists[index], oldspeak, newspeak);
}

//Returns the num of non-NULL ll in the hash table
uint32_t ht_count(HashTable *ht) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i] != NULL) {
            count++;
        }
    }
    return count;
}

void ht_print(HashTable *ht) {
    for (uint32_t i = 0; i < ht->size; i++) {
        if (ht->lists[i]) {
            ll_print(ht->lists[i]);
        }
    }
    return;
}

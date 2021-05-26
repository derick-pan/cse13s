//Derick Pan
//dpan7
//bf.c
#include "bf.h"

#include "bv.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Following struct is from Asgn7 documentation.
typedef struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt.
    uint64_t secondary[2]; // Secondary hash function salt.
    uint64_t tertiary[2]; // Tertiary hash function salt.
    BitVector *filter;
} BloomFilter;

//Constructor function for BloomFilter from Asgn7 documentation
BloomFilter *bf_create(uint32_t size) {
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));
    if (bf) {
        // Grimm's Fairy Tales
        bf->primary[0] = 0x5adf08ae86d35f21;
        bf->primary[1] = 0xa267bbd3116f3957;
        // The adventures of Sherlock Holmes
        bf->secondary[0] = 0x419d292ea2ffd49e;
        bf->secondary[1] = 0x09601433057d5786;
        // The Strange Case of Dr. Jekyll and Mr. Hyde
        bf->tertiary[0] = 0x50d8bb08de3818df;
        bf->tertiary[1] = 0x4deaae187c16ae1d;
        bf->filter = bv_create(size);
        if (!bf->filter) {
            free(bf);
            bf = NULL;
        }
    }
    return bf;
}

void bf_delete(BloomFilter **bf) {
    free(*bf);
    *bf = NULL;
}

//Return size of bf the Bloom Filter
uint32_t bf_size(BloomFilter *bf) {
    //return length of underlying bit vector
    return bv_length(bf->filter);
}

//Takes oldspeak and inserts into bloom filter
void bf_insert(BloomFilter *bf, char *oldspeak) {
    // Hashing oldspeak with each of three salts for 3 indices
    // Setting the bits at those indices in underlying bit vector
    uint32_t first = hash(bf->primary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, first);
    uint32_t second = hash(bf->secondary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, second);
    uint32_t third = hash(bf->tertiary, oldspeak) % bf_size(bf);
    bv_set_bit(bf->filter, third);
    return;
}

//Check if the bits at those indces are set
//Returns true if oldspeak is probably in
bool bf_probe(BloomFilter *bf, char *oldspeak) {
    uint32_t first = hash(bf->primary, oldspeak) % bf_size(bf);
    uint32_t second = hash(bf->secondary, oldspeak) % bf_size(bf);
    uint32_t third = hash(bf->tertiary, oldspeak) % bf_size(bf);
    //printf("First: %u, Second %u, Third %u \n", first, second, third);
    return (bv_get_bit(bf->filter, first) && bv_get_bit(bf->filter, second)
            && bv_get_bit(bf->filter, third));
}

//Return the num of set bits in Bloom Filter
uint32_t bf_count(BloomFilter *bf) {
    uint32_t count = 0;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (bv_get_bit(bf->filter, i) == 1) {
            count++;
        }
    }
    return count;
}

void bf_print(BloomFilter *bf) {
    for (uint8_t i = 0; i < bf_size(bf); i++) {
        printf("%u", bv_get_bit(bf->filter, i));
    }
    printf("\n");
    return;
}

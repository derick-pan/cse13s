//Derick Pan
//dpan7
//bv.c
#include "bv.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* bit vector code is mostly all reused from my asgn5 */

//byte_length from Dr.Long
#define byte_length(x) ((x / 8) + !!(x % 8))

typedef struct BitVector {
    uint32_t length; //Length in bits.
    uint8_t *vector; //Array of bytes.
} BitVector;

BitVector *bv_create(uint32_t length) { //Inspired by Dr.Long
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    v->length = length;
    v->vector = (uint8_t *) calloc(byte_length(length), sizeof(uint8_t));
    for (uint8_t i = 0; i < (length / 8 + 1); i++) {
        bv_clr_bit(v, 0);
    }
    return v;
}

void bv_delete(BitVector **v) {
    free((*v)->vector);
    free(*v);
    *v = NULL;
    return;
}

//Returns the length of bit vector
uint32_t bv_length(BitVector *v) {
    return v->length;
}

//Sets ith bit in bit vector               i = position of bit
void bv_set_bit(BitVector *v, uint32_t i) { //Inspired by Dr.Long
    v->vector[i / 8] |= 0x1 << (i % 8);
    return;
}

// Clears ith bit in bit vector               i = position of bit
void bv_clr_bit(BitVector *v, uint32_t i) { //Inspired by Dr.Long
    v->vector[i / 8] &= ~(0x1 << (i % 8));
    return;
}

//Get the bit
uint8_t bv_get_bit(BitVector *v, uint32_t i) { //Inspired by Dr.Long
    return (v->vector[i / 8] >> (i % 8) & 0x1);
}

void bv_print(BitVector *v) {
    for (uint8_t i = 0; i < byte_length(v->length); i++) {
        printf("%u ",bv_get_bit(v, i));
    }
}

//Derick Pan
//dpan7
//Asgn5
//Bit vector bv.c
#include "bv.h"
#include "bm.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define byte_length(x) ((x / 8) + !!(x % 8))

//1 d array
typedef struct BitVector {
    uint32_t length; //Length in bits.
    uint8_t *vector; //Array of bytes.
} BitVector;

BitVector *bv_create(uint32_t length) { //Inspired by Dr.Long
    BitVector *v = (BitVector *) malloc(sizeof(BitVector));
    v->length = length;
    v->vector = (uint8_t *) calloc(byte_length(length), sizeof(uint8_t));
    for (uint8_t i = 0; i < length; i++) {
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
    v->vector[i / 8] |= (uint32_t) 0x1 << (i % 8);
    return;
}

// Clears ith bit in bit vector               i = position of bit
void bv_clr_bit(BitVector *v, uint32_t i) { //Inspired by Dr.Long
    v->vector[i / 8] &= ~((uint32_t) 0x1 << (i % 8));
    return;
}

// XOR
void bv_xor_bit(BitVector *v, uint32_t i, uint8_t bit) {
    v->vector[i / 8] ^= (uint32_t) bit << (i % 8);
    return;
}

//Get the bit
uint8_t bv_get_bit(BitVector *v, uint32_t i) { //Inspired by Dr.Long
    return (v->vector[i / 8] >> (i % 8) & 0x1);
}

void bv_print(BitVector *v) {
    for (uint8_t i = 0; i <= byte_length(v->length); i++) {
        v->vector[i] = 0;
    }
}

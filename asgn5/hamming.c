//Derick Pan
//dpan7
//Asgn5
//hamming.c
#include "hamming.h"

#include "bm.h"
#include "bv.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int total;
int uncorrected;
int corrected;

int lookup(uint8_t e) {
    int moves[] = { HAM_OK, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2, HAM_ERR,
        1, 0, HAM_ERR };
    return moves[e];
}
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    //if msg is 4 bits then generate c by vector matrix multiplication
    // c = mG

    BitMatrix *temp = bm_from_data(msg, 4); //Convert Binary into matrix

    BitMatrix *mult = bm_multiply(temp, G); //Mult matrix with G

    uint8_t encoded = bm_to_data(mult);
    bm_delete(&temp);
    bm_delete(&mult);
    return encoded;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    total += 1;
    BitMatrix *codeMat = bm_from_data(code, 8); // Code in matrix form
    BitMatrix *mult = bm_multiply(codeMat, Ht);
    uint8_t ebinary = bm_to_data(mult); //  Convert E into binary
    code &= 0xF;
    if (lookup(ebinary) == HAM_OK) { //No correction is needed, return HAM_OK
        *msg = code;
        bm_delete(&codeMat);
        bm_delete(&mult);
        return HAM_OK;
    }
    if (lookup(ebinary) == HAM_ERR) {
        uncorrected += 1;
        bm_delete(&codeMat);
        bm_delete(&mult);
        return HAM_ERR;
    }
    if (lookup(ebinary) > 4) {
        *msg = code; //This is 8 bits

    } else if (bm_get_bit(codeMat, 0, lookup(ebinary)) == 1) {
        bm_clr_bit(codeMat, 0, lookup(ebinary));
        *msg = bm_to_data(codeMat);
    } else {
        bm_set_bit(codeMat, 0, lookup(ebinary));
        *msg = bm_to_data(codeMat);
    }
    corrected += 1;
    bm_delete(&codeMat);
    bm_delete(&mult);
    return HAM_CORRECT;
}

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

int lookup(uint8_t e) {
    int moves[] = { -3, 4, 5, HAM_ERR, 6, HAM_ERR, HAM_ERR, 3, 7, HAM_ERR, HAM_ERR, 2, HAM_ERR, 1,
        0, HAM_ERR };
    return moves[e];
}
uint8_t ham_encode(BitMatrix *G, uint8_t msg) {
    //if msg is 4 bits then generate c by vector matrix multiplication
    // c = mG
    BitMatrix *temp = bm_from_data(msg, 4);
    BitMatrix *mult = bm_multiply(temp, G);
    uint8_t encoded = bm_to_data(mult);
    bm_delete(&mult);
    bm_delete(&temp);
    return encoded;
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg) {
    //BitMatrix *codeMat= bm_from_data(code, 8); // Code in matrix form
    //BitMatrix *e= ;  //  e = Code * * transposed
    uint8_t ebinary
        = bm_to_data(bm_multiply(bm_from_data(code, 8), Ht)); //  e = Code * * transposed
    //uint8_t ebinary = bm_to_data(bm_multiply(codeMat, Ht));  //  e = Code * * transposed
    //bm_delete(&codeMat);

    if (lookup(ebinary) == HAM_OK) { //No correction is needed, return HAM_OK
        return HAM_OK;
    } else if (lookup(ebinary) == HAM_ERR) {
        return HAM_ERR;
    }

    BitMatrix *message = bm_from_data(*msg, 4);
    if (bm_get_bit(message, 0, lookup(ebinary)) == 1) { //Flip 1 to 0
        bm_clr_bit(message, 0, lookup(ebinary));
        *msg = bm_to_data(message);
    } else { //Flip 0 to 1
        bm_set_bit(message, 0, lookup(ebinary));
        *msg = bm_to_data(message);
    }
    bm_delete(&message);
    return HAM_CORRECT;
}

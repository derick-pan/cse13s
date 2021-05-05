//Derick Pan
//dpan7
//Asgn5
//hamming.c
#include "bm.h"
#include "bv.h"
#include "hamming.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

uint8_t lower_nibble ( uint8_t val ) {
    return val & 0xF ;
}
// Returns the upper nibble of val
uint8_t upper_nibble ( uint8_t val ) {
    return val >> 4;
}
// Packs two nibbles into a byte
uint8_t pack_byte ( uint8_t upper , uint8_t lower ) {
    return ( upper << 4) | (lower & 0xF) ;
}

int lookup(uint8_t e){
    int moves[] = {-3,4,5,HAM_ERR,6,HAM_ERR,HAM_ERR,3,7,HAM_ERR,HAM_ERR,2,HAM_ERR,1,0,HAM_ERR};
    return moves[e];
}
uint8_t ham_encode(BitMatrix *G, uint8_t msg){
//if msg is 4 bits then generate c by vector matrix multiplication
// c = mG
    BitMatrix *temp= bm_from_data(msg, 4);
    BitMatrix *mult= bm_multiply(temp, G);
    bm_delete(&temp);
    return bm_to_data(mult);
}

HAM_STATUS ham_decode(BitMatrix *Ht, uint8_t code, uint8_t *msg){

    BitMatrix *codeMat= bm_from_data(code, 8); // Code
    BitMatrix *e= bm_multiply(codeMat, Ht);  //Code * * transposed
    uint8_t code = bm_to_data(e);
    bm_delete(&codeMat);
    if(lookup(code)==HAM_OK){
        return HAM_OK;
    }
    else{
        if(bm_get_bit(codeMat, 0, lookup(code))==1){
            bm_clr_bit(codeMat, 0, lookup(code));
        }
        else{
            bm_set_bit(codeMat,0, lookup(code));
        }
    }



    for (uint8_t i =0; i <4; i++){

    }
    //if e ==0:
        //We chilling
    //else
        //lookup(e)
}

//Derick Pan
//dpan7
//Asgn5
//bm.c Bit matrix ADT
#include "bm.h"
#include "bv.h"
#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define bitnum(r, cols, c) r *cols + c

//Serves as a wrapper over bitVector
typedef struct BitMatrix {
    uint32_t rows;
    uint32_t cols;
    BitVector *vector;
} BitMatrix;

BitMatrix *bm_create(uint32_t rows, uint32_t cols) {
    BitMatrix *m = (BitMatrix *) malloc(sizeof(BitMatrix));
    m->rows = rows;
    m->cols = cols;
    uint32_t matlength = rows * cols;
    m->vector = bv_create(matlength);
    for (uint8_t i = 0; i < m->rows; i++) {
        for (uint8_t j = 0; j < m->cols; j++) {
            bm_clr_bit(m, i, j);
        }
    }
    return m;
}

void bm_delete(BitMatrix **m) {
    bv_delete(&(*m)->vector);
    free((*m)->vector);
    free(*m);
    *m = NULL;
}

//return num of rows
uint32_t bm_rows(BitMatrix *m) {
    return m->rows;
}
//return num of cols
uint32_t bm_cols(BitMatrix *m) {
    return m->cols;
}

//Sets bit at row r and col c
void bm_set_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_set_bit(m->vector, bitnum(r, m->cols, c));
    return;
}

//Clears bit at row r and col c
void bm_clr_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    bv_clr_bit(m->vector, bitnum(r, m->cols, c));
    return;
}

//Gets bit at row r and col c
uint8_t bm_get_bit(BitMatrix *m, uint32_t r, uint32_t c) {
    return bv_get_bit(m->vector, bitnum(r, m->cols, c));
}

// Convert Binary into a Matrix
BitMatrix *bm_from_data(uint8_t byte, uint32_t length) {
    BitMatrix *newmatrix = bm_create(1, length);
    uint8_t i = 0;
    while (byte) {
        if (byte & 1) { //If first bit is 1:
            bm_clr_bit(newmatrix, 0, i);
            bm_set_bit(newmatrix, 0, i);
        } else { //If first bit is 0:
            bm_clr_bit(newmatrix, 0, i);
        }
        byte >>= 1; //Right shift by 1
        i += 1;
    }
    return newmatrix;
}
//Extract first 8 bits of matrix, and return.
uint8_t bm_to_data(BitMatrix *m) {
    uint8_t data = 0;
    uint8_t temp;
    for (uint8_t j = 0; j < 8; j++) {
        temp = bm_get_bit(m, 0, j) << j;
        data |= temp;
    }
    return data;
}

//  Multiply matrices
BitMatrix *bm_multiply(BitMatrix *A, BitMatrix *B) {
    BitMatrix *multiplied = bm_create(bm_rows(A), bm_cols(B));
    for (uint8_t k = 0; k < A->cols; k++) {
        for (uint8_t i = 0; i < B->cols; i++) { //Iterate over the A matrix
            uint8_t temp = 0;
            for (uint8_t j = 0; j < A->cols; j++) { //Iterate over the B matrix
                uint8_t abit = bm_get_bit(A, k, j) * bm_get_bit(B, j, i); //Value of A's
                temp = temp + abit; //XOR previous vals
            }
            temp = temp % 2;
            if (temp == 1) {
                bm_set_bit(multiplied, k, i);
            } else {
                bm_clr_bit(multiplied, k, i);
            }
        }
    }
    return multiplied;
}

void bm_print(BitMatrix *m) {
    for (uint8_t i = 0; i < m->rows; i++) {
        for (uint8_t j = 0; j < m->cols; j++) {
            printf("%u ", bm_get_bit(m, i, j));
        }
        printf("\n");
    }
    return;
}

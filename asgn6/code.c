//Derick Pan
//dpan7
//code.c
#include "code.h"
#include "defines.h"
#include "stack.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Defining variables for ease of use.
  BLOCK         4096          // 4KB blocks.
  ALPHABET      256           // ASCII + Extended ASCII.
  MAGIC         0xDEADBEEF    // 32-bit magic number.
  MAX_CODE_SIZE (ALPHABET / 8) // Bytes for a maximum, 256-bit code.
  MAX_TREE_SIZE (3 * ALPHABET - 1) // Maximum Huffman tree dump size.*/

// Constructor function for code with NO dynamic memory allocation
Code code_init(void) {
    Code c;
    c.top = 0;
    for (uint32_t i = 0; i < MAX_CODE_SIZE; i++) { //For loop to zero out the bits
        c.bits[i] = 0;
    }
    return c;
}

//return the number of bits pushed onto the code
uint32_t code_size(Code *c) {
    return c->top;
}

//Return True if code is empty
bool code_empty(Code *c) {
    if (c->top == 0) {
        return true;
    }
    return false;
}

//return true if code is full
bool code_full(Code *c) {
    if (c->top == MAX_CODE_SIZE) {
        return true;
    }
    return false;
}

uint32_t code_get_bit(Code *c, uint8_t i) { //Inspired by Dr.Long
    return (c->bits[i / 8] >> (i % 8) & 0x1);
}

// Push one bit at a time, Returns true if it worked
bool code_push_bit(Code *c, uint8_t bit) {
    if (code_full(c)) {
        return false;
    }
    //if bit == 1 set and shift 1 into place
    if (bit == 1) {
        c->bits[c->top / 8] |= 0x1 << (c->top % 8);
    } //else clear the top
    else {
        c->bits[c->top / 8] &= ~(0x1 << (c->top % 8));
    }
    c->top += 1;
    return true;
}

//Pop a bit off the code
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    c->top -= 1; //decrement c->top
    //Get the bit and pass it back through pointer
    *bit = code_get_bit(c, c->top);
    return true;
}

// Debug function to print the code
void code_print(Code *c) {
    printf("Print code:\n");
    for (uint32_t i = 0; i < c->top; i++) {
        printf("%u ", c->bits[i / 8] >> (i % 8) & 0x1);
        if (i % 8 == 7) {
            printf("\n");
        }
    }
    printf("\n");
}

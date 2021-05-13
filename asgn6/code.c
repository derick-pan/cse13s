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
/*#define           BLOCK         4096          // 4KB blocks.
#define             ALPHABET      256           // ASCII + Extended ASCII.
#define             MAGIC         0xDEADBEEF    // 32-bit magic number.
#define             MAX_CODE_SIZE (ALPHABET / 8) // Bytes for a maximum, 256-bit code.
#define             MAX_TREE_SIZE (3 * ALPHABET - 1) // Maximum Huffman tree dump size.

typedef struct Code {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE]; // Array of 32 uint8_t's
} Code;*/
//We want to be able to pass a struct by value

//Stack of bits while traversing the tree in order to create a code for each symbol

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
    if (c->top == ALPHABET - 1) {
        return true;
    }
    return false;
}

uint32_t code_get_bit(Code *c, uint8_t i) { //Inspired by Dr.Long
    return (c->bits[i / 8] >> (i % 8) & 0x1);
}

bool code_push_bit(Code *c, uint8_t bit) { // Push one bit at a time
    if (code_full(c)) {
        return false;
    }
    c->bits[c->top / 8] |= bit << (c->top % 8);
    c->top += 1;
    return true;
}
//Pop a bit off the code
bool code_pop_bit(Code *c, uint8_t *bit) {
    if (code_empty(c)) {
        return false;
    }
    // the bit will be in this array: c->bits[c->top/8] at index: [c->top % 8]
    c->top -= 1; //decrement c->top

    //*bit = c->bits[c->top / 8] >> (c->top % 8) & 0x1; //Get the bit
    *bit = code_get_bit(c, c->top);
    c->bits[c->top / 8] &= ~(0x1 << (c->top % 8)); //Clear the bit
    return true;
}

void code_print(Code *c) {
    printf("Print code:\n");
    for (uint32_t i = 0; i < c->top; i++) { //For loop to zero out the bits
        printf("%u ", c->bits[i / 8] >> (i % 8) & 0x1);
        if (i % 8 == 7) {
            printf("\n");
        }
    }
    printf("\n");
}

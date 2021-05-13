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
/*#define           BLOCK         4096 // 4KB blocks.
#define             ALPHABET      256 // ASCII + Extended ASCII.
#define             MAGIC         0xDEADBEEF // 32-bit magic number.
#define             MAX_CODE_SIZE (ALPHABET / 8) // Bytes for a maximum, 256-bit code.
#define             MAX_TREE_SIZE (3 * ALPHABET - 1) // Maximum Huffman tree dump size.

typedef struct Code {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;*/
//We want to be able to pass a struct by value

//Stack of bits while traversing the tree in order to create a code for each symbol

Code code_init(void) {
    Code c;
    c.top = 0;
    //For loop to zero out the bits
    return c;
}

uint32_t code_size(Code *c);

bool code_empty(Code *c);

bool code_full(Code *c);

bool code_push_bit(Code *c, uint8_t bit); // Push one byte at a time and iterate over the bits

bool code_pop_bit(Code *c, uint8_t *bit);

void code_print(Code *c);

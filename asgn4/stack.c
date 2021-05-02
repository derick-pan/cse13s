//Derick Pan
//dpan7
//Asgn4
#include "stack.h"

#include "vertices.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*Most of these helper functions are my functions from Asgn3's stack*/
typedef struct Stack { //This struct is from the asg4_Doc.pdf
    uint32_t top; //Index of next mt slot
    uint32_t capacity; // # of items can push
    uint32_t *items; // Array of items,
} Stack;

Stack *stack_create(uint32_t capacity) { //Function from asg4_Doc.pdf
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) { //Function from asg4_Doc.pdf
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

uint32_t stack_size(Stack *s) { //Returns # of items in stack
    return s->top;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

bool stack_push(Stack *s, uint32_t x) { //Pushes x to top of stack if success return True, else F
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1; //Next avaliable spot
    return true;
}
bool stack_pop(Stack *s, uint32_t *x) { //pops item off stack, return T or F for success or not
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    *x = s->items[s->top];
    return true;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top - 1];
    return true;
}

//Make dst same as src
void stack_copy(Stack *dst, Stack *src) {
    for (uint32_t items = 0; items < src->top; items++) {
        dst->items[items] = src->items[items];
    }
    dst->top = src->top;
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}

// Derick Pan
// dpan 7
// stack.c
#include "stack.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
} Stack;

//Allocate Memory for stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node *)); //allocating array of node pointers
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

//Deallocate memory for stack
void stack_delete(Stack **s) {
    if (*s) {
        if ((*s)->top > 0) {
            node_delete((*s)->items);
        }
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
}

//return true if stack is empty
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

//return true if stack is full
bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

//Return the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

//Push a node onto the stack
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = n;
    s->top += 1; // Top points to the next empty spot to add
    return true;
}

//Pops a node off the stack passing it back through pointer
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1; //Decrease the top because that is the new & next empty spot
    *n = s->items[s->top];
    return true;
}

//Function to print a stack
void stack_print(Stack *s) {
    for (uint32_t i = 0; i < s->top; i += 1) {
        node_print(s->items[i]);
    }
    printf("(•_•)\n<)   )╯\n/\n");// prints out a fun stick man to indicate end of stackprint.
    return;
}

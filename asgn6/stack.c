// Derick Pan
// dpan 7
// stack.c

#include "stack.h"

#include <stdlib.h>

typedef struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
} Stack;

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items =
    }
}

void stack_delete(Stack **s);

bool stack_empty(Stack *s);

bool stack_full(Stack *s);

uint32_t stack_size(Stack *s);

bool stack_push(Stack *s, Node *n);

bool stack_pop(Stack *s, Node **n);

void stack_print(Stack *s);

//Derick Pan
//dpan7
//Asgn3
#include "stack.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Stack { //This struct is from the asg3_Doc.pdf
    uint32_t top; //Index of next mt slot
    uint32_t capacity; // # of items can push
    int64_t *items; // Array of items,
} Stack;

//Creates function
Stack *stack_create(uint32_t capacity) { //Function from asg3_Doc.pdf
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}
//Destructor Function
//Frees  all memory allocated by the constructor
void stack_delete(Stack **s) { //Function from asg3_Doc.pdf
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_full(Stack *s) {
    //Not in the .h file
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}
uint32_t stack_size(Stack *s) { //Returns # of items in stack
    return s->top;
}
bool stack_push(Stack *s, int64_t x) { //Pushes x to top of stack if success return True, else F
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1; //Next avaliable spot
    return true;
}
bool stack_pop(Stack *s, int64_t *x) { //pops item off stack, return T or F for success or not

    if (stack_empty(s)) {
        return false;
    }
    s->top -= 1;
    //set value in memory x is pointing to popped item
    *x = s->items[s->top]; //Line from asgn3_Doc.pdf
    //So I changed the pointer,
    return true;
}
void stack_print(Stack *s) {
    for (uint32_t i = 0; i < stack_size(s); i += 1) {
        printf("%ld\n", s->items[i]);
    }
    printf("-------------------------------------------------\n");
    return;
}

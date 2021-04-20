//Derick Pan
//dpan7
//Asgn3
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "stack.h"

struct Stack { //This struct is from the asg3_Doc.pdf
	uint32_t top;		//Index of next mt slot
	uint32_t capacity;	// # of items can push
	int64_t *items;		// Array of items,
};


Stack *stack_create(uint32_t capacity) { //Function from asg3_Doc.pdf
	Stack *s = (Stack *) malloc(sizeof(Stack));
	if (s) {
		s->top = 0;
		s->capacity = capacity;
		s->items = (int64_t *) calloc(capacity, sizeof(int64_t));
		if (!s->items) {
			free(s);
			s=NULL;
		}
	}
	return s;
}

void stack_delete(Stack **s) {//Function from asg3_Doc.pdf
	if (*s && (*s)->items) {
		free((*s)->items);
		free(*s);
		*s = NULL;
	}
	return;
}

bool stack_empty(Stack **s);

uint32_t stack_size(Stack *s);

bool stack_push(Stack *s, int64_t x);

bool stack_pop(Stack *s, int64_t *x);

void stack_print(Stack *s);




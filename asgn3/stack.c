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

//Creates function
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
//Destructor Function
//Frees  all memory allocated by the constructor
void stack_delete(Stack **s) {//Function from asg3_Doc.pdf
	if (*s && (*s)->items) {
		free((*s)->items);
		free(*s);
		*s = NULL;
	}
	return;
}
//bool stack_full(Stack *s);
	//Not in the .h file
	//
bool stack_empty(Stack *s);
	if (s->top ==0){
		return 1;
uint32_t stack_size(Stack *s);//Returns # of items in stack
	return sizeof(s)/sizeof(uint32_t);	

bool stack_push(Stack *s, int64_t x);//Pushes x to top of stack if success return True, else F
	//uint32_t spot = (s->top+1) % (s->capacity); //index of Next avaliable spot
	if (s[s->top] == NULL){
		s[s->top] = x ;
		s->top += 1;
		return true;
	}
	return false;	

bool stack_pop(Stack *s, int64_t *x);//pops item off stack, return T or F for success or not
	
void stack_print(Stack *s);




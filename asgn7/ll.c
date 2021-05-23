//Derick Pan
//dpan7
//ll.c
#include "ll.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

uint64_t seeks; // Number of seeks performed.
uint64_t links; // Number of links traversed.

//Struct is from asgn7 documentation
typedef struct LinkedList{
	uint32_t length;
	Node *head;
	Node *tail;
	bool mtf;
} LinkedList;

LinkedList *ll_create(bool mtf){
	LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
	if (ll) {
		ll->mtf = mtf;
		//Initialized with exactly 2 sentinel nodes
		ll->head = node_create(0,0);
		ll->tail = node_create(0,0);

	}
	return ll;
}

void ll_delete(LinkedList **ll);

//Return length of ll
uint32_t ll_length(LinkedList *ll){
	int len = 0;
//Return the # of nodes in the linked list excluding the head and tail sentinel nodes
	Node *current = ll->head;
	while (current != NULL){
		current = current->next;
		len++;
	}
	return len-2; //Subtract head and tail
}

Node *ll_lookup(LinkedList *ll, char *oldspeak){
	Node *current = ll->head;
	Node *past = NULL, *future = NULL;
	while (current != NULL){
		if (strcmp(current->oldspeak, oldspeak)){
			//Found the node
			if (ll->mtf ){
				//Move current to front of the linked list
				//Take current out of current position
				past->next = current->next;
				future->prev = current->prev;
				//Place it infront of head and redirect pointers on right side
				(ll->head->next)->prev = current;
				current->next = (ll->head)->next;
				//Redirect pointers on left side
				current->prev = ll->head;
				(ll->head)->next = current;
			}
			return current;
		}
		past = current;
		current = current->next;
		future = current->next;
	}
	return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak){
	if (ll_lookup(ll, oldspeak)){
		//don't insert
		return;
	}
	Node *node = node_create(oldspeak, newspeak);
	(ll->head->next)->prev = node;	//Right side of node
	node->next = (ll->head)->next;

	node->prev = ll->head;		//Left side of node
	(ll->head)->next = node;
	return;
}

void ll_print(LinkedList *ll){

	Node *current = ll->head->next;
	while (current != ll->tail){
		node_print(current);
		current = current->next;
	}
}

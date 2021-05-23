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
	while (current != NULL){
		if (strcmp(current->oldspeak, oldspeak)){
			//Found the node
			break;
			//If mtf{}
		}
		current = current->next;
	}
	return current;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak){

	if (ll_lookup(ll, oldspeak)){
		//don't insert
		return;
	}
	Node *node = node_create(oldspeak, newspeak);
	ll->head->next->prev = node->next; //redirect the original node's prev person
	ll->head->next = node->prev;	//Redirect heads next person
	return;
}

void ll_print(LinkedList *ll){
	Node *current = ll->head->next;
	while (current != ll->tail){
		node_print(current);
		current = current->next;
	}
}

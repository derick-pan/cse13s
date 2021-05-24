//Derick Pan
//dpan7
//ll.c
#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
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
		printf("I'm in here\n");
		ll->mtf = mtf;
		ll->length = sizeof(LinkedList);
		//Initialized with exactly 2 sentinel nodes
		ll->head = node_create(NULL,NULL);
		ll->tail = node_create(NULL,NULL);
		ll->head->next = ll->tail;
		ll->tail->next = NULL;
		ll->tail->prev = ll->head;

	}
	printf("Create fail\n");
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
	printf("in lookup\n");
	Node *current = ll->head->next;
	Node *past = NULL, *future = NULL;

	printf("in lookup2\n");
	while (current != ll->tail){
		printf("O\n");
		printf("current %s ",current->oldspeak);
		printf("test current %s\n",oldspeak);
		if (strcmp(current->oldspeak,oldspeak)==0){
			//Found the node
			printf("hereee456\n\n");
			if (ll->mtf){
				//Move current to front of the linked list
				//Take current out of current position
				printf("hereee412356\n\n");
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
			//break;
		}
		//past = current;
		current = current->next;
		//future = current->next;
	}
	printf("returned null\n");
	return NULL;
}

void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak){
	if (ll_lookup(ll, oldspeak)!= NULL){
		//don't insert
		return;
	}

	printf("past lookup\n");
	Node *node = node_create(oldspeak, newspeak);
	printf("ll_insert crash \n");
	node->next = (ll->head)->next;
	node->prev = ll->head;		//Left side of node
	(ll->head->next)->prev= node;	//Right side of node
	ll->head->next = node;

	printf("Why crash  here tho\n");
	return;
}

void ll_print(LinkedList *ll){

	Node *current = ll->head->next;
	while (current != ll->tail){
		node_print(current);
		current = current->next;
	}
}

//Derick Pan
//dpan7
//node.c
#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "ll.h"
#include "node.h"
#include "parser.h"
#include "speck.h"

#include <ctype.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/*
struct Node {
    char *oldspeak;
    char *newspeak;
    Node *next;
    Node *prev;
};*/

typedef struct Node Node;
//Each node contains a pointer to previous node and the next node in the ll
//Function that mimics strdup()

// Constructor function for Node
Node *node_create(char *oldspeak, char *newspeak) {
  //Allocate memory and copy character of oldspeak
  //Allocate memory and copy character of newspeak

	Node *n = (Node *) malloc(sizeof(Node));

	printf("Have I made it here 1?\n");
	if (oldspeak!=NULL){
 		n->oldspeak = strdup(oldspeak);
	}
	else{
		n->oldspeak=NULL;
	}
	printf("Have I made it here2 ?\n");
	if (newspeak!=NULL){
		n->newspeak = strdup(newspeak);
	}
	else{
		n->newspeak=NULL;
	}
	n->next = NULL;
	n->prev = NULL;
  return n;

}

//Destructor Function for Node
void node_delete(Node **n){
	free(*n);
	free((*n)->oldspeak);
	free((*n)->newspeak);
	*n = NULL;
}

//Following prinf statements are from Asgn7 doc
void node_print(Node *n){
	//If node contains both old and newspeak then print
	if (n->oldspeak && n->newspeak){
		printf("%s -> %s\n", n->oldspeak, n->newspeak);
	}
	else{ //Just print oldspeak
	printf("%s\n",n->oldspeak);
	}

}

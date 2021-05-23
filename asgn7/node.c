//Derick Pan
//dpan7
//node.c
#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
struct Node {
    char *oldspeak;
    char *newspeak;
    Node *next;
    Node *prev;
};*/
typedef struct Node Node;

//Function that mimics strdup()
char *stringdup(char *before){
	int size = strlen(before)+1;
	char *string = malloc(size);
	memcpy(string,before,size);
	return string;
}

// Constructor function for Node
Node *node_create(char *oldspeak, char *newspeak) {
  //Allocate memory and copy character of oldspeak
  //Allocate memory and copy character of newspeak
	Node *n = (Node *) malloc(sizeof(Node));
 	n->oldspeak = stringdup(oldspeak);
  	n->newspeak = stringdup(newspeak);
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

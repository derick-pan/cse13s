// Derick Pan
// dpan7
// ll.c
#include "ll.h"

#include "bf.h"
#include "bv.h"
#include "ht.h"
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
typedef struct LinkedList {
    uint32_t length; // Length of Linked List
    Node *head; // Head sentinel node
    Node *tail; // Tail Sentinel Node
    bool mtf;
} LinkedList;

//Constructor Function
LinkedList *ll_create(bool mtf) {
    LinkedList *ll = (LinkedList *) malloc(sizeof(LinkedList));
    if (ll) {
        ll->mtf = mtf;
        ll->length = 0;
        //Initialized with exactly 2 sentinel nodes
        ll->head = node_create(NULL, NULL);
        ll->tail = node_create(NULL, NULL);
        ll->head->next = ll->tail;
        ll->tail->next = NULL;
        ll->head->prev = NULL;
        ll->tail->prev = ll->head;
    }
    return ll;
}

//Each node in linked list should be freed using node_delete
//then set pointer to null
void ll_delete(LinkedList **ll) {
    if (*ll) {
        Node *current = (*ll)->head;

        while (current) {
            Node *next = current->next;
            node_delete(&current);
            current = next;
        }
        free(*ll);
        *ll = NULL;
    }
}

//Return length of ll
uint32_t ll_length(LinkedList *ll) {
    return ll->length;
}

//Search for a node containing oldspeak
Node *ll_lookup(LinkedList *ll, char *oldspeak) {
    seeks += 1; //Increment the amount of linked list lookups
    Node *current = ll->head->next;
    while (current != ll->tail) {
        if (strcmp(current->oldspeak, oldspeak) == 0) { //if node found
            if (ll->mtf) {
                //Remove the current node from it's position
                (current->next)->prev = (current->prev);
                (current->prev)->next = (current->next);
                //Place the node behind the head.
                current->next = (ll->head)->next;
                current->prev = ll->head;
                (ll->head->next)->prev = current;
                ll->head->next = current;
            }
            return current;
        }
        links++;
        current = current->next;
    }
    return NULL;
}

//Inserts a new node with oldspeak and newspeak
void ll_insert(LinkedList *ll, char *oldspeak, char *newspeak) {
    if (ll_lookup(ll, oldspeak) != NULL) {
        return;
    }
    ll->length++;
    Node *node = node_create(oldspeak, newspeak);
    node->next = (ll->head)->next;
    node->prev = ll->head; //Left side of node
    (ll->head->next)->prev = node; //Right side of node
    ll->head->next = node;
    return;
}

//Prints out the linked lists excluding head and sentinel nodes.
void ll_print(LinkedList *ll) {
    Node *current = ll->head->next;
    while (current != NULL) {
        node_print(current);
        current = current->next;
    }
}

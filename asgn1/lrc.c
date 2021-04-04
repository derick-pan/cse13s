#include "philos.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//This struct creates a data set to remember the name, # of $, and position
typedef struct {
    char name[50];
    int cash;
    int pos;
} variables;

//returns the position of the player on the left
//pos: Position of the current player
//players: The number of players in the game.
static inline uint8_t left(uint8_t pos, uint8_t players) { //from lab1 documentation
    return ((pos + players - 1) % players);
}
//returns the position of the player on the right
static inline uint8_t right(uint8_t pos, uint8_t players) { //from lab1 documentation
    return ((pos + 1) % players);
}

//In function Money, Player rolls a die, and does the move cooresponding to die face.
//a = player,  players = # of players, variables ppl[14] = struct and max possible array
int money(int a, unsigned int players, variables ppl[14]) {
    typedef enum faciem {
        PASS,
        LEFT,
        RIGHT,
        CENTER
    } faces; //The following two lines from lab1 documentation
    faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
    int rando = rand() % 6;
    if (die[rando] == LEFT) { //Get position of person on left, and give them a dollar
        uint8_t leftt = left(a, players);
        ppl[leftt].cash = ppl[leftt].cash + 1;
        ppl[a].cash = ppl[a].cash - 1;
        printf(" gives $1 to %s", ppl[leftt].name);
        return 0;
    } else if (die[rando] == RIGHT) { //Gets position of person on right, and give them a dollar
        uint8_t rightt = right(a, players);
        ppl[rightt].cash = ppl[rightt].cash + 1;
        ppl[a].cash = ppl[a].cash - 1;
        printf(" gives $1 to %s", ppl[rightt].name);
        return 0;
    } else if (die[rando] == CENTER) { //Put a dollar into the Center
        ppl[a].cash = ppl[a].cash - 1;
        printf(" puts $1 in the pot");
        return 1;
    } else {
        printf(" gets a pass");
        return 0;
    }
}

//Function check, checks if the game should keep going.
int check(unsigned int players, variables ppl[14]) {
    unsigned int i = 0;
    int cashtest = 0;
    for (i = 0; i < players; i++) {
        if (ppl[i].cash > 0) { //if only one person has cash then cashtest =1
            cashtest = cashtest + 1;
        }
    }
    if (cashtest == 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    //Ask for the random seed and the amount of players
    unsigned int seed;
    printf("Random seed: ");
    scanf("%u", &seed);
    srandom(seed);

    unsigned int players;
    printf("How many players? ");
    if (scanf("%u", &players) == EOF || players > 14 || players < 1) {
        //Check for invalid input
        printf("Number of players must be from 1 to 14.\n");
        return 0;
    }
    int pot = 0; // Holds the amount in the center pot
    variables ppl[players];

    unsigned int i;
    for (i = 0; i < players; i++) { //Create an array of data
        strcpy(ppl[i].name, philosophers[i]);
        ppl[i].cash = 3;
        ppl[i].pos = i;
    }

    if (players == 1) { //Condition if there's only one player
        printf("%s wins the $%d pot with $%d left in the bank!\n", ppl[0].name, pot, ppl[0].cash);
        return 0;
    }

    /*While loop only runs if game can keep running> loop over all the players>
    if statements that execute corresponding to the amount of money a player has. */
    while (check(players, ppl) == 0) {
        unsigned int a;
        for (a = 0; a < players; a++) { //Loop over al the players
            if (ppl[a].cash == 0) {
                continue;
            } else if (ppl[a].cash == 2) {
                //roll 2 dice
                printf("%s rolls...", ppl[a].name); //Name rolls...
                pot = pot + money(a, players, ppl);
                pot = pot + money(a, players, ppl);
                printf("\n");
            } else if (ppl[a].cash == 1) {
                printf("%s rolls...", ppl[a].name); //Name rolls...
                pot = pot + money(a, players, ppl);
                printf("\n");
            } else {
                printf("%s rolls...", ppl[a].name); //Name rolls...
                pot = pot + money(a, players, ppl);
                pot = pot + money(a, players, ppl);
                pot = pot + money(a, players, ppl);
                printf("\n");
            }

            if (check(players, ppl) == 1) {
                unsigned int j;
                for (j = 0; j < players; j++) {
                    if (ppl[j].cash >= 1) {
                        printf("%s wins the $%d pot with $%d left in the bank!\n", ppl[j].name, pot,
                            ppl[j].cash);
                        return 0;
                    }
                }
            }
        }
    }
}

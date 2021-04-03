#include <stdio.h>
#include "philos.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct {
	char name[50];
	int cash;
	int pos;
		}variables;
        //returns the position of the player on the left
        //pos: Position of the current player
        //players: The number of players in the game.
        //The following two lines are from the asgn1.pdf lab1 documentation.
static inline uint8_t left(uint8_t pos, uint8_t players) {
        return ((pos + players - 1) % players);
	}
        //returns the position of the player on the right
        //The following two lines are from the asgn1.pdf lab1 documentation.
static inline uint8_t right(uint8_t pos, uint8_t players) {
        return ((pos + 1) % players);
	}
        //The following two lines are from the asgn1.pdf lab1 documentation
int money(int a, unsigned int players , variables ppl[14]){ //give money to l/r/pot/pass
	typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
		faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };
	int rando = rand() % 6;
	if (die[rando] == LEFT ){
		uint8_t leftt = left(a, players);//Get person on left position
		ppl[leftt].cash = ppl[leftt].cash + 1; //Give a dollar
		ppl[a].cash = ppl[a].cash -1;//Lose a dollar
		printf(" gives $1 to %s", ppl[leftt].name);
		return 0;	
		}
	else if (die[rando] == RIGHT){
		uint8_t rightt = right(a, players);
		ppl[rightt].cash = ppl[rightt].cash + 1;
		ppl[a].cash = ppl[a].cash - 1;
		printf(" gives $1 to %s", ppl[rightt].name);
		return 0;
		}


	else if (die[rando] == CENTER){
		ppl[a].cash = ppl[a].cash -1;
		printf(" puts $1 in the pot");
		return 1;
		}
	else{
		printf(" gets a pass");
		return 0;
		}
}
int check(unsigned int players, variables ppl[14]){ //Check if the game should keep going
	unsigned int i = 0;
	int cashtest = 0;
	for (i=0; i<players; i++){
		if (ppl[i].cash > 0){ //if only one person has cash then cashtest =1
		    cashtest = cashtest +1;
			}	    
		}
	if (cashtest ==1){
		return 1;
		}
	else{
		return 0;
		}
	}	
int main(){
	//Ask for the random seed and the amount of players
	unsigned int seed;
	printf("Random seed: ");
	scanf("%u", &seed);
	srandom(seed);
	unsigned int players;
	printf("How many players? ");
	if(scanf("%u", &players)==EOF||players > 14 || players < 1 ){	
		printf("Number of players must be from 1 to 14.\n");
		return 0;
		}
	int pot = 0;
	variables ppl[players];
	unsigned int i;
	for (i =0; i<players; i++){ //Create an array of data		
		strcpy(ppl[i].name, philosophers[i]);
		ppl[i].cash = 3;
		ppl[i].pos = i;
		}	
	
	if (players ==1){
                printf("%s wins the $%d pot with $%d left in the bank!\n", ppl[0].name,pot, ppl[0].cash);
		return 0;
		}
	while(check(players, ppl) ==0) {
		unsigned int a;
		for (a=0; a<players; a++){
			if (ppl[a].cash == 0){	
				continue;
				}
			else if (ppl[a].cash ==2){
				//roll 2 dice
				printf("%s rolls...", ppl[a].name); //Name rolls... 
				pot = pot + money(a,players, ppl);
				pot = pot + money(a,players, ppl);
				printf("\n");
				}
			else if (ppl[a].cash == 1){ 
				printf("%s rolls...", ppl[a].name); //Name rolls... 
                                pot = pot + money(a,players, ppl);
				printf("\n");
				
				}
			else{
                                printf("%s rolls...", ppl[a].name); //Name rolls... 
                                pot = pot + money(a,players, ppl);
                                pot = pot + money(a,players, ppl);
				pot = pot + money(a,players, ppl);
				printf("\n");
				}

			if (check(players,ppl) ==1){
				unsigned int j;
				for (j=0; j<players; j++){
					if (ppl[j].cash >= 1){		
						printf("%s wins the $%d pot with $%d left in the bank!\n", ppl[j].name,pot, ppl[j].cash);
						return 0 ;
						}
					}
				}
			}
		}
}

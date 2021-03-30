#include <stdio.h>
#include <philos.h> /*Does this work? */

main()
	
{
	//returns the position of the player on the left
	//pos: Position of the current player
	//players: The number of players in the game.

	//The following two lines are from the asgn1.pdf lab1 documentation.
	static inline uint8_t left (unit8_t pos, unit8_t players) {
		return ((pos + players - 1) % players);

	//returns the position of the player on the right
        //The following two lines are from the asgn1.pdf lab1 documentation.
	static inline unit8_t right(unit8_t pos, unit8_t players) {
		return ((pos + 1) % players);

        //The following two lines are from the asgn1.pdf lab1 documentation.
	typedef enum faciem { PASS, LEFT, RIGHT, CENTER } faces;
	faces die[] = { LEFT, RIGHT, CENTER, PASS, PASS, PASS };}

	while () //While 1 >= # of players with $

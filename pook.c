/*
	POOK
	a poker game by josh and claude 

	main game file
*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "deck.h"
#include "table.h"


// helper functions
void invokeMove();


int main(void) {
	
	// declare variables
	int nplayers, i, chips, round, sb, bb, ante;
	bool playFlag, turnFlag;
	char name[256];
	char quit;
	Player p;

	// create a new table
	Table t = newTable();

	/*    !!!   create players   !!!    */
	// get number of players
	printf("players: ");
	scanf("%d", &nplayers);

	// get starting chips
	printf("starting chips: ");
	scanf("%d", &chips);

	// set blinds
	printf("enter blinds and ante (bb sb ante): ");
	scanf("%d %d %d", &bb, &sb, &ante);
	setBlinds(t, bb, sb, ante);

	// create players
	for (i = 0; i < nplayers; i++) {
		// get player name
		printf("enter name for player %d: ", i);
		scanf("%s", name);
		
		// create player
		p = newPlayer(name, chips);

		// add player to table
		addPlayer(p, t);
		printf("%s has joined the table\n", name);

		// reset player name string
		memset(name, 0, 256);
	}

	printf("\n\n\n");

	// create a deck of cards
	Deck d = newStandardDeck();

	// initalize flags and variables
	round = 0;
	playFlag = true;


	/*
		loop and play an entire round
		until a player quits the games
	*/
	while(playFlag) {

		// start a new round
		initRound(t);

		playStreets(t);
	}

	// free table
	freeTable(t);
}























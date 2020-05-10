/*
	POOK
	a poker game by josh and claude 

	main game file
*/

//#include "deck.h"
#include "table.h"


int main(void) {
	// create 5 new players
	Player claude = newPlayer("Claude", 1000);
	Player josh = newPlayer("Josh", 3);
	Player pat = newPlayer("Pat", 9000);
	Player phil = newPlayer("Phil Ivey", 400);
	Player dan = newPlayer("Daniel Negroonoo", 8999);

	// create a new table
	Table t = newTable();

	// add players to the table
	addPlayer(claude, t);
	addPlayer(josh, t);
	addPlayer(pat, t);
	addPlayer(phil, t);
	addPlayer(dan, t);

	// print table
	printTable(t);

	// free players
	freePlayer(claude);
	freePlayer(josh);
	freePlayer(pat);
	freePlayer(phil);
	freePlayer(dan);

	// free table
	freeTable(t);

}
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

	// deal cards to the players
	dealCards(t);

	// print table
	printTable(t);

	// remove players from the table
	removePlayer(t, 3);	// 5	
	removePlayer(t, 2);	// 4
	removePlayer(t, 0);	// 3
	//printf("after removing players, 3, 2, 0:\n");
	//printTable(t);
	removePlayer(t, 1);	// 2
	removePlayer(t, 0);	// 1

	// free table
	freeTable(t);
}
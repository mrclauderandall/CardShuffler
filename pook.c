/*
	POOK
	a poker game by josh and claude 

	main game file
*/

//#include "deck.h"
#include "table.h"


int main(void) {
	// create a new player
	Player p = newPlayer("Claude", 500);

	// free Player p
	freePlayer(p);

}
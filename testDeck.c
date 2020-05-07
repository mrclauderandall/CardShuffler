// test file for deck implementation
// written by FyRel

#include "deck.h"
#include <stdio.h>

int main(void) {

	// create a new deck
	Deck d = newStandardDeck();

	// show the deck
	showDeck(d);

	// free deck
	freeDeck(d);

	return 0;	
}
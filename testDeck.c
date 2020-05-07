// test file for deck implementation
// written by FyRel

#include "deck.h"
#include "riffle.h"
#include <stdio.h>

int main(void) {

	// create a new deck
	Deck d = newStandardDeck();

	// show the deck
	showDeck(d);
    
	// riffle deck 7 times and show deck after each riffle
	for (int i = 0; i < 4; i++) {
		// riffle deck
    	riffle(d, 0);
    	
    	//show the deck riffled
    	showDeck(d);
	}
 
	// free deck
	freeDeck(d);

	return 0;
}

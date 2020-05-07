// test file for deck implementation
// written by FyRel

#include "deck.h"
#include "riffle.h"
#include <stdio.h>

int main(void) {

	// create a new deck
	Deck d = newStandardDeck();

	// show the deck
	printf("original deck: ");
	showDeck(d);
	printf("\n\n");
    
	// riffle deck 7 times and show deck after each riffle
	for (int i = 0; i < 4; i++) {
		printf("now starting riffle shuffle number %d\n", i);

		// riffle deck
    	riffle(d, 0);
    	
    	//show the deck riffled
    	printf("after riffle number %d:		d->size = %d\n", i, d->size);
    	showDeck(d);
    	printf("\n");
	}
 
	// free deck
	freeDeck(d);

	return 0;
}

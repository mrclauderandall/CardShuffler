// test file for deck implementation 

#include "deck.h"
#include <stdio.h>

int main(void) {

	// create a new deck
	Deck d = newStandardDeck();

	// print the deck
	printf("original deck:\n");
	showDeck(d);

	// perfect riffle shuffle deck
	
	for (int i = 0; i < 9; i++) {
		printf("\nriffle shuffling deck:\n");
		d = riffle(d, 0);
		showDeck(d);
	}
	

	// show deck
	

	// free deck
	freeDeck(d);

	return 0;	
}
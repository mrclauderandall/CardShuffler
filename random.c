// randomness 

#include <stdio.h>
#include "deck.h"
#include "random.h"

int orderRetainment(Deck d1, Deck d2) {
	
	// check both decks are valid
	if (d1 == NULL || d2 == NULL) {
		printf("invalid decks given to orderRetainment\n");
		exit(1);
	}

	// check both decks are the same size
	if (deckSize(d1) != deckSize(d2)) {
		printf("decks must be the same size\n");
		exit(1);
	}

	// declare variables
	Card cur1, cur2;
	int order = 0;
	int found;

	// loop through checking cards for order
	cur1 = d1->top;
	while (cur1 != NULL) {
		
		// find the equivalent cur1 card in d2
		found = 0;
		cur2 = d2->top;
		while (cur2 != NULL) {
			if (equivalentCards(cur1, cur2)) {
				found = 1;
				
				if (equivalentCards(cur1->bellow, cur2->bellow)) {
					order++;
				}
				
				break;
			}

			cur2 = cur2->bellow;
		}

		if (found == 0) {
			printf("card was not found\n");
			return -1;
		}

		cur1 = cur1->bellow;
	}

	return order;
}







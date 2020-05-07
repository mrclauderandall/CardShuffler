// riffle algorithm implementation
// written by FyRel

#include "deck.h"
#include "riffle.h"

Deck riffle(Deck d, int kind) {

	/*
	kind:
		0 	perfect shuffle
		1	human like shuffle
	*/

	// check valid deck
	if (d == NULL) {
		printf("this deck is empty\n");
		exit(1);
	} else if (d->size < 2) {
		printf("cannot shuffle a deck with less than 2 cards\n");
	}

	// declare variables
	int size;
	int count = 0;
	DoubleDeck dd;
	Deck return_deck;
	Card c, insert_card;

	// get size to cut the deck
	if (kind == 0) {
		size = 26;
	} else if (kind == 1) {
		size = left_deck(0);
	} else {
		printf("[riffle] must specifiy kind of riffle shuffle\n0	perfect shuffle\n1	human life inperfect shuffle\n");
		exit(1);
	}

	// cut the deck
	dd = cutDeck(d, size);

	// riffle shuffle deck
	if (kind == 0) {
		c = dd->right->bottom;
		while (c != NULL) {
			if ((count % 2) == 0) {
				insert_card = removeBottomCard(dd->left);
				insert_card->bellow = c;

				if (c == dd->right->top) {
					c->above = insert_card;
					dd->right->top = insert_card;
				} else {
					insert_card->above = c->above;
					c->above = insert_card;
					insert_card->above->bellow = insert_card;
				}
			}

			c = c->above;
			count++;
		}
	}

	// assign the return deck to the right deck
	return_deck = dd->right;

	// free double deck structure
	freeDeck(dd->left);
	free(dd);

	// return the right deck
	return return_deck;
}


int left_deck(int a) {

	// generate random number [0:99]
	srand(time(NULL) + a);
	int r = rand() % 100;

	// determine size of left deck
	int n = 26;

	if (r < 2) {
		n = 21;
	} else if (r < 4) {
		n = 31;
	} else if (r < 7) {
		n = 22;
	} else if (r < 10) {
		n = 30;
	} else if (r < 15) {
		n = 23;
	} else if (r < 20) {
		n = 29;
	} else if (r < 30) {
		n = 24;
	} else if (r < 40) {
		n = 28;
	} else if (r < 55) {
		n = 25;
	} else if (r < 70) {
		n = 27;
	}

	return n;
}



DoubleDeck cutDeck(Deck d, int size) {
	// allocate memory for new DDeck
	DoubleDeck dd = malloc(sizeof(*dd));

	// initalized the double deck
	dd->left = newEmptyDeck();
	dd->right = d;											// assumption 3

	// get random number
	int left_deck_size = left_deck(0);

	// loop through removing cards and adding them
	// to the left double deck
	Card c;													// assumption 2
	for (int i = 0; i < size; i++) {
		c = removeBottomCard(d);
		dd->left = addCard(c, dd->left, 0);
	}

	return dd;
}






// deck data structure implementation
// written by FyRel

#include "deck.h"

// * * * helper functions * * *

Card newCard(char suit, int value) {
	Card c = malloc(sizeof(*c));

	if (c == NULL) {
		fprintf(stderr, "couldn't allocate memory for card\n");
		exit(EXIT_FAILURE);
	}

	c->suit = suit;
	c->value = value;
	c->bellow = NULL;
	c->above = NULL;

	return c;
}

void freeCard(Card c) {
	if (c == NULL) {
		return;
	} else {
		c->above = NULL;
		c->bellow = NULL;
		free(c);
	}
}

// create a new empty deck
Deck newEmptyDeck(void) {
	// allocate memory for the new deck
	// and initialize values
	Deck d = malloc(sizeof(*d));
	d->top = NULL;
	d->bottom = NULL;
	d->size = 0;

	// check memory was allocated correctly
	if (d == NULL) {
		fprintf(stderr, "couldn't allocate memory for the deck\n");
		exit(EXIT_FAILURE);
	}

	return d;
}

// create a new ordered deck
Deck newStandardDeck(void) {

	// initalize new empty deck
	Deck d = newEmptyDeck();

	// declare variables for card creating
	Card c;
	int v;
	char s;

	// make each card in the standard deck
	// and add it to the deck
	for (int i = 0; i < 4; i++) {
		// set the suit
		switch (i) {
			case 0:
				s = 's'; break;
			case 1:
				s = 'h'; break;
			case 2:
				s = 'c'; break;
			default:
				s = 'd';
		}

		// create a card for each value of the suit
		for (int v = 14; v >= 2; v--) {

			// create the card
			c = newCard(s, v);

			// add the card to the deck
			d = addCard(c, d, 0);
		}
	}

	return d;
}

// add a card to a deck
Deck addCard(Card c, Deck d, int pos) {
	// check valid deck and card
	if (d == NULL || c == NULL) {
		printf("addCard: must pass valid deck and card\n");
		return d;
	}

	// check if deck is empty
	if (d->top == NULL) {
		d->top = c;
		d->bottom = c;
	} else if (pos == 0) {
		// insert card at top of deck
		d->top->above = c;
		d->top->above->bellow = d->top;
		d->top = d->top->above;
	} else if (pos < 0 || pos >= d->size) {
		// insert card at the bottom of deck
		c->above = d->bottom;
		d->bottom->bellow = c;
		d->bottom = c;
	} else {
		// insert card in the middle

		// declare variables
		int i = 0;
		Card cur = d->top;

		// move cur into correct position
		while (i < pos && cur != NULL) {
			cur = cur->bellow;
			i++;
		}

		// insert card
		c->above = cur->above;
		c->bellow = cur;
		cur->above->bellow = c;
		cur->above = c;
	}

	// incrament size and return
	d->size++;
	return d;
}


/*
	remove a card from the deck in position pos
	e.g:
	0  -> remove top card
	1  -> remove the card under the top card
	4  -> remove the 4th card (0 indexed)
	-1 -> remove bottom card
	if pos > size of deck, also remove
	bottom card
*/
Card removeCard(Deck d, int pos) {
	if (d->size == 0) {
		printf("cannot remove a card from an empty deck:\ndeck given:\n");
		showDeck(d);
		exit(1);
	}

	// declare variables
	Card cur =  d->top;
	int i = 0;

	// check if there is only 1 card and
	// check if removing top or bottom card
	// and if not remove the positional card
	if (d->size == 1) {
		// remove the last card in the deck
		d->top = NULL;
		d->bottom = NULL;
	} else if (pos == 0) {
		// unlink top card from card bellow
		d->top = d->top->bellow;
		d->top->above = NULL;
	} else if (pos < 0 || pos >= d->size) {
		// unlink bottom card from card above
		d->bottom = d->bottom->above;
		d->bottom->bellow = NULL;
	} else {
		// loop through to correct card
		while (i < pos && cur != NULL) {
			cur = cur->bellow;
			i++;
		}

		// edit links
		cur->bellow->above = cur->above;
		cur->above->bellow = cur->bellow;
	}

	// unlink cur
	cur->above = NULL;
	cur->bellow = NULL;

	// deincrament and return
	d->size--;
	return cur;
}




// remove and return the top card from the deck
Card removeTopCard(Deck d) {

	if (d->size == 0) return newCard('x', 0);

	// set card c as the top card
	Card c = d->top;

	// check this is not the last card
	if (d->top == d->bottom) {
		c = d->top;
		d->top = NULL;
		d->bottom = NULL;
	} else {
		// remove links between top card
		// and the card bellow it
		d->top->bellow->above = NULL;
		d->top = d->top->bellow;
		c->bellow = NULL;
	}

	// deincrament size of deck
	d->size--;

	// return the top card
	return c;
}

Card removeBottomCard(Deck d) {
	if (d->size == 0) return newCard('x', 0);

	// set card c as the bottom card
	Card c = d->bottom;

	// check this is not the last card
	if (d->top == d->bottom) {
		//c = d->top;
		d->top = NULL;
		d->bottom = NULL;
	} else {
		// remove links between bottom card
		// and the card above it
		d->bottom = d->bottom->above;
		d->bottom->bellow = NULL;
		c->above = NULL;
	}

	// deincrament size of deck
	d->size--;

	// return the top card
	return c;
}

// print out entire deck to stdin
void showDeck(Deck d) {

	Card c = d->top;

	if (c == NULL) {
		printf("this deck is empty\n");
		return;
	}

	printf("TOP->");
	while (c != NULL) {

		printCard(c);
		printf(" ");

		if (c == d->bottom) {
			break;
		} else {
			c = c->bellow;
		}
	}
	printf("<-BOTTOM\n");
}

// free all memory used for the deck
void freeDeck(Deck d) {
	Card c = d->top;

	while (c != NULL) {
		Card temp = c;
		c = c->bellow;
		freeCard(temp);
	}
	free(d);
}

void printCard(Card c) {
	if (c == NULL) return;

	switch (c->value) {
		case 11:
			printf("J%c", c->suit); break;
		case 12:
			printf("Q%c", c->suit); break;
		case 13:
			printf("K%c", c->suit); break;
		case 14:
			printf("A%c", c->suit); break;
		default:
			printf("%d%c", c->value, c->suit);
	}
}



/*
	cut the deck "around about"
	half way, and then return
	two seperate decks in DDeck

	allocate memory for the new
	DDeck

	destoy old deck
*/

bool equivalentDecks(Deck d1, Deck d2) {

	// check if same size
	if (d1->size != d2->size) return false;

	// declare variables
	Card cur1 = d1->top;
	Card cur2 = d2->top;

	// loop through checking each card
	while (cur1 != NULL && cur2 != NULL) {
		if (cur1->value != cur2->value || cur1->suit != cur2->suit) {
			return false;
		}

		cur1 = cur1->bellow;
		cur2 = cur2->bellow;
	}

	return true;
}

int cardPosition(Deck d, Card c) {

	// declare variables
	Card cur = d->top;
	int count = 0;

	// loop through deck searching for card c
	while (cur != NULL) {
		
		// check if current card is card c
		if (cur->value == c->value && cur->suit == c->suit) {
			// return position of the card
			return count;
		}

		cur = cur->bellow;
	}

	// card was not found, return -1
	return -1;
}





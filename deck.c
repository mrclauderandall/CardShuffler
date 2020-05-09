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
	int s, i;
	int v = 12;

	// make each card in the standard deck
	// and add it to the deck
	for (int s = 3; s > 1; s--) {
		// create a card for each value of the suit
		for (int i = 0; i < 13; i++) {
			// modulo v
			v = v % 13;
			
			// create the card
			c = newCard(s, v);

			// add the card to the deck
			addCard(c, d, 0);

			// incrament value
			v++;
		}
	}

	v = 11;
	for (s = 1; s >= 0; s--) {
		// create a card for each value of the suit
		for (int i = 0; i < 13; i++) {
			// modulo v
			v = v % 13;
			
			// create the card
			c = newCard(s, v);

			// add the card to the deck
			addCard(c, d, 0);

			// incrament value
			v--;

			if (v < 0) {
				v = 12;
			}
		}
	}

	return d;
}

// add a card to a deck
void addCard(Card c, Deck d, int pos) {
	// check valid deck and card
	if (d == NULL || c == NULL) {
		printf("addCard: must pass valid deck and card\n");
		return;
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

	// incrament size
	d->size++;
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
	if (deckSize(d) == 0) {
		printf("cannot remove a card from an empty deck:\ndeck given:\n");
		showDeck(d);
		exit(1);
	}

	// declare variables
	Card cur;
	int i = 0;

	// check if there is only 1 card and
	// check if removing top or bottom card
	// and if not remove the positional card
	if (d->size == 1) {
		// remove the last card in the deck
		cur = d->top;
		d->top = NULL;
		d->bottom = NULL;
	} else if (pos == 0) {
		// unlink top card from card bellow
		cur = d->top;
		d->top = d->top->bellow;
		d->top->above = NULL;
	} else if (pos < 0 || pos >= (deckSize(d) - 1)) {
		// unlink bottom card from card above
		cur = d->bottom;
		d->bottom = d->bottom->above;
		d->bottom->bellow = NULL;
	} else {
		// loop through to correct card
		cur = d->top;
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

// print out entire deck to stdin
void showDeck(Deck d) {

	Card cur = d->top;

	if (cur == NULL) {
		printf("this deck is empty\n");
		return;
	}

	printf("size: %d\n", deckSize(d));
	printf("TOP-> ");
	while (cur != NULL) {

		printCard(cur);
		printf(" ");

		cur = cur->bellow;
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
	if (c == NULL) printf("NULL\n");
	
	switch (valueCard(c)) {
		case 0:
			printf("2"); break;
		case 1:
			printf("3"); break;
		case 2:
			printf("4"); break;
		case 3:
			printf("5"); break;
		case 4:
			printf("6"); break;
		case 5:
			printf("7"); break;
		case 6:
			printf("8"); break;
		case 7:
			printf("9"); break;
		case 8:
			printf("10"); break;
		case 9:
			printf("J"); break;
		case 10:
			printf("Q"); break;
		case 11:
			printf("K"); break;
		case 12:
			printf("A"); break;
		default:
			printf("!value error!");
	}

	switch (suitCard(c)) {
		case 0:
			printf("h"); break;
		case 1:
			printf("c"); break;
		case 2:
			printf("d"); break;
		case 3:
			printf("s"); break;
		default:
			printf("!suit error!\n");
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
		count++;
	}

	// card was not found, return -1
	return -1;
}

int deckSize(Deck d) {
	if (d == NULL) return -1;
	
	return d->size;
}

Card copyCard(Card c) {
	if (c == NULL) return NULL;
	
	return newCard(suitCard(c), valueCard(c));
}

// return the value of card c
int valueCard(Card c) {
	if (c == NULL) {
		printf("invalid card given to function valueCard\n");
		exit(1);
	}

	return c->value;
}

// return the suit of card c
int suitCard(Card c) {
	if (c == NULL) {
		printf("invalid card given to function suitCard\n");
		exit(1);
	}

	return c->suit;
}

Deck copyDeck(Deck d) {	
	Deck new_deck = newEmptyDeck();
	Card cur = d->top;
	while (cur != NULL) {
		addCard(copyCard(cur), new_deck, -1);
		cur = cur->bellow;
	}
	return new_deck;
}

// check to see if two cards are the same
bool equivalentCards(Card c1, Card c2) {
	if (suitCard(c1) == suitCard(c2) && valueCard(c1) == valueCard(c2)) return true;

	return false;
}








// deck data structure implementation
// written by FyRel

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <assert.h>

#include "deck.h"

struct card {
	int value, suit;
	Card above, bellow;
};

struct deck {
	Card top, bottom;
	int size;
};

/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ helper definitions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	used for human riffle shuffle; determine the next card to be
	released. Probability is based on the size of the two decks, 
	(meaning if one deck is much larger, it has a larger chance
	of releaseing the card) as well as the last card that was 
	released. the Variable a is needed for the random seed, if 
	calling rChance more than once within a short amount of time, 
	(e.g. in a loop), incrament a to give a different random seed
*/
bool rChance(int a, int left_size, int right_size, int last_card);

/*
	return the size of the left cut deck
	the returned value is a 'rough' / random
	value emulating how a human cuts a deck

	note: if called multiple times withing
	the time frame of 1 second, all instances
	will be the same value unless the input
	'a' is changed between instances. In
	normal usage, a can be left as 0.
*/
int leftDeckSize(int a);

// return a random number between min and max
int randomB(int a, int lower, int upper);






/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Card ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

Card newCard(int suit, int value) {
	Card c = malloc(sizeof(struct card));

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

Card copyCard(Card c) {
	if (c == NULL) return NULL;
	
	return newCard(suitCard(c), valueCard(c));
}

int valueCard(Card c) {
	if (c == NULL) {
		return -1;
	}

	return c->value;
}

int suitCard(Card c) {
	if (c == NULL) {
		return -1;
	}

	return c->suit;
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

Card getCard(Deck d, int pos) {
	// check valid deck
	if (d == NULL) {
		printf("addCard: must pass valid deck and card\n");
		return NULL;
	}

	// check deck is not empty
	if (d->size == 0) {
		return NULL;
	}

	// check if pos is the bottom card
	if (pos < 0 || pos >= d->size - 1) {
		
		return d->bottom;
	}

	// loop through deck until c reaches pos
	Card c = d->top;

	for (int i = 0; i < pos; i++) {
		c = c->bellow;
	}

	return c;
}

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

Card removeCard(Deck d, int pos) {
	if (deckSize(d) == 0) {
		printf("cannot remove a card from an empty deck:\ndeck given:\n");
		printDeck(d);
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

bool equivalentCards(Card c1, Card c2) {
	if (suitCard(c1) == suitCard(c2) && valueCard(c1) == valueCard(c2)) return true;

	return false;
}





/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Deck ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

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

void freeDeck(Deck d) {
	if (d == NULL) return;


	Card c = d->top;

	while (c != NULL) {
		Card temp = c;
		c = c->bellow;
		freeCard(temp);
	}
	free(d);
}

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

int deckSize(Deck d) {
	if (d == NULL) return -1;
	
	return d->size;
}

bool deckIsEmpty(Deck d) {
	assert(d != NULL);

	return (d->size == 0); 
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

Deck cutDeck(Deck d, int size) {
	// allocate memory for new DDeck
	Deck left = malloc(sizeof(*left));

	// initalized the double deck
	left = newEmptyDeck();

	// loop through removing cards and adding them
	// to the left deck
	int i = 0;
	while (i < size && deckSize(d) > 0) {
		addCard(removeCard(d, -1), left, 0);
		i++;
	}

	return left;
}

void shuffle(Deck d) {
	// check d is a valid deck
	// check valid deck
	if (d == NULL) {
		printf("this deck is empty\n");
		exit(1);
	} else if (d->size < 2) {
		printf("cannot shuffle a deck with less than 2 cards\n");
		exit(1);
	}

	// declare variables
	Card cur = d->top;
	Card t;
	int count = 0;
	int a = 0;
	int pos_d, pos_t;
	Deck temp = newEmptyDeck();

	/* 
		randomly remove all the cards 
		in deck d and add them to an 
		empty deck
	*/
	while (deckSize(d) > 0) {
		pos_d = randomB(a, 0, deckSize(d));
		pos_t = randomB((a+1), 0, deckSize(temp));
		addCard(removeCard(d, pos_d), temp, pos_t);
		a++;
	}

	/*
		randomly remove and put back 
		all the cards into deck d
	*/
	while (deckSize(temp) > 0) {
		pos_d = randomB(a, 0, deckSize(d));
		pos_t = randomB((a+1), 0, deckSize(temp));
		addCard(removeCard(temp, pos_t), d, pos_d);
		a++;

	}

	// free the empty deck
	if (deckSize(temp) != 0) {
		printf("shuffle failed\n");
		exit(1);
	}

	freeDeck(temp);
}





/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ printing and testing ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

void printDeck(Deck d) {

	Card cur = d->top;

	if (cur == NULL) {
		printf("X");
		return;
	}

	while (cur != NULL) {
		printCard(cur);
		printf(" ");
		cur = cur->bellow;
	}
}

void printCard(Card c) {
	if (c == NULL) printf("NULL");
	
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
			printf("!suit error!");
	}
}

void printC(Card c) {
	assert (c != NULL);
	printf("%d%d", c->value, c->suit);
}

void printD(Deck d) {
	Card cur = d->top;

	if (cur == NULL) {
		printf("X");
		return;
	}

	printf("(vs): ");
	while (cur != NULL) {
		printC(cur);
		printf(" ");
		cur = cur->bellow;
	}
}

Deck newTestDeck(void) {
	Deck d = newEmptyDeck();

	for (int s = 0; s < 4; s++) {
		for (int v = 0; v < 10; v++) {
			Card c = newCard(s, v);
			addCard(c, d, -1);
		}
	}

	return d;
}



/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ helper functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

int leftDeckSize(int a) {

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

bool rChance(int a, int left_size, int right_size, int last_card) {
	double l = (double)left_size;
	double r = (double)right_size;
	double split = (l / r) * 50;
	split += last_card;
	srand(time(NULL) + a);
	int ran = rand() % 100;
	if (ran < split) return true;
	
	return false;
}

int randomB(int a, int lower, int upper) {
	srand(time(NULL) + a);
	int m = upper - lower + 1;
	int num = (rand() % m) + lower;
	return num;
}





/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ riffle functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

void rifflePerfect(Deck d) {
	// check valid deck
	if (d == NULL) {
		printf("this deck is empty\n");
		exit(1);
	} else if (d->size < 2) {
		printf("cannot shuffle a deck with less than 2 cards\n");
		exit(1);
	}

	// declare variables
	int size = deckSize(d) / 2;
	int count = 0;
	Card insert_card;

	// cut the deck
	Deck l = cutDeck(d, size);

	// initalize cur
	Card cur = d->bottom;

	// loop through
	while (cur != NULL) {
		if ((count % 2) == 0) {
			insert_card = removeCard(l, -1);
			insert_card->bellow = cur;

			if (cur == d->top) {
				cur->above = insert_card;
				d->top = insert_card;
			} else {
				insert_card->above = cur->above;
				cur->above = insert_card;
				insert_card->above->bellow = insert_card;
			}

			d->size++;
		} 

		cur = cur->above;
		count++;
	}
}

void riffleHuman(Deck d) {
	// check valid deck
	if (d == NULL) {
		printf("this deck is empty\n");
		exit(1);
	} else if (d->size < 2) {
		printf("cannot shuffle a deck with less than 2 cards\n");
		exit(1);
	}

	// declare variables
	int size = leftDeckSize(0);
	int a = 0;
	int last_card = 0;
	Card insert_card;

	// cut the deck
	Deck l = cutDeck(d, size);

	// get original size of right deck
	int right_size = deckSize(d);

	// initalize cur
	Card cur = d->bottom;

	// loop through
	while (cur != NULL && deckSize(l) > 0) {
		if (rChance(a, deckSize(l), right_size, last_card)) {
			//printf("left\n");
			insert_card = removeCard(l, -1);
			insert_card->bellow = cur;

			if (cur == d->top) {
				cur->above = insert_card;
				d->top = insert_card;
			} else {
				insert_card->above = cur->above;
				cur->above = insert_card;
				insert_card->above->bellow = insert_card;
			}

			last_card = -30;
			d->size++;
		} else {
			//printf("right\n");
			right_size--;
			last_card = 30;
		}


		a++;
		cur = cur->above;
	}

	//
	if (deckSize(l) != 0) {
		l->bottom->bellow = d->top;
		d->top->above = l->bottom;
		d->top = l->top;
		d->size += deckSize(l);
	}

	l->size = 0;
	l->bottom = NULL;
	l->top = NULL;
	free(l);
}




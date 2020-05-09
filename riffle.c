// riffle algorithm implementation
// written by FyRel

#include <stdbool.h>

#include "deck.h"
#include "riffle.h"


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

bool rChance(int a, int left_size, int right_size, int last_card) {
	// calculate split
	double l = (double)left_size;
	double r = (double)right_size;

	//printf("left_size = %f, right_size = %f, last_card = %d\n", l, r, last_card);



	double split = (l / r) * 50;
	split += last_card;
	//printf("split = %f\n", split);

	// generate random number [0:99]
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


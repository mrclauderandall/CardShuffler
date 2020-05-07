// riffle algorithm implementation
// written by FyRel

#include <stdbool.h>

#include "deck.h"
#include "riffle.h"

bool rChance(int a);

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
	Card insert_card;

	// cut the deck
	Deck l = cutDeck(d, size);

	// initalize cur
	Card cur = d->bottom;

	// loop through
	while (cur != NULL && deckSize(l) > 0) {
		if (rChance(a)) {
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

bool rChance(int a) {
	// generate random number [0:99]
	srand(time(NULL) + a);
	int r = rand() % 100;

	if (r < 51) return true;

	return false;
}




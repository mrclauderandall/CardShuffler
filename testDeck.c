// test file for deck implementation
// written by FyRel

#include "deck.h"
#include "riffle.h"
#include <stdio.h>
#include <assert.h>

// test function definitions
void test_addCard(void);

int main(void) {

	// create a new deck
	Deck d = newStandardDeck();

	// test addCard


	// free deck
	freeDeck(d);

	return 0;
}


void test_addCard(void) {

	// CASE 1: empty deck
	// create two empty decks and two valid card
	Deck d1 = newEmptyDeck();
	Deck d2 = newEmptyDeck();
	Card c1 = newCard('t', 1);
	Card c2 = newCard('t', 2);

	// add card to d1
	addCard(c1, d1, 0);

	// check card is in d1
	assert(cardPosition(d1, c1) == 0);
	assert(d1->top->value == 1);
	assert(d1->bottom->value == 1);

	// add card with large number position
	addCard(c2, d2, 99);
	assert(cardPosition(d2, c2) == 0);
	assert(d2->top->value == 2);
	assert(d2->bottom->value == 2);

	// free decks and card
	freeDeck(d1);
	freeDeck(d2);
	printf("t_addCard: test 1 passed\n");

	// CASE 2: add to middle of 2 card deck
	// create a deck and 3 cards
	Deck d = newEmptyDeck();
	addCard(newCard('h', 2), d, 0);
	addCard(newCard('d', 2), d, -1);
	addCard(newCard('s', 2), d, 1);
	
	assert(d->top->suit == 'h');
	assert(d->bottom->suit == 'd');
	assert(d->top->bellow->suit == 's');

	freeDeck(d);
	printf("t_addCard: test 2 passed\n");

	// CASE 3: add a card to a middle position of a standard deck
	d = newStandardDeck();
	Card c = newCard('t', 0);
	addCard(c, d, 10);

	assert(cardPosition(d, c) == 10);

	printf("t_addCard: test 3 passed\n");
}








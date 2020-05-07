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
	test_addCard();


	// free deck
	freeDeck(d);

	return 0;
}


void test_addCard(void) {
	// CASE 0: invalid deck / card
	// create a valid and invalid deck and card
	Deck valid_d = newEmptyDeck();
	Deck invalid_d = NULL;
	Card valid_c = newCard('t', 0);
	Card invalid_c = NULL;
	
	assert(addCard(valid_c, invalid_d, 0) == invalid_d);
	assert(addCard(invalid_c, valid_d, 0) == valid_d);
	free(valid_d);
	free(valid_c);
	printf("t_addCard: test 0 passed\n");

	// CASE 1: empty deck
	// create two empty decks and a valid card
	Deck d1 = newEmptyDeck();
	Deck d2 = newEmptyDeck();
	Card c = newCard('t', 0);

	// add card to d1
	d1 = addCard(c, d1, 0);

	// check card is in d1
	assert(cardPosition(d1, c) == 0);
	assert(d1->top->value == 0);
	assert(d1->bottom->value == 0);

	// add card with large number position
	d2 = addCard(c, d2, 99);
	assert(cardPosition(d2, c) == 0);
	assert(d2->top->value == 0);
	assert(d2->bottom->value == 0);

	// free decks and card 				<<<<<<<<<<<<<<<<<<<<<< for josh to look at
	showDeck(d1);
	showDeck(d2);

	freeDeck(d1);

	showDeck(d1);
	showDeck(d2);
	
	freeDeck(d2);

	showDeck(d1);
	showDeck(d2);

	freeCard(c);

	showDeck(d1);
	showDeck(d2);

	printf("test 1 passed\n");

	// CASE 2: add to middle of 2 card deck
	// create a deck and 3 cards


	// CASE 3: add a card to a middle position of a standard deck
}








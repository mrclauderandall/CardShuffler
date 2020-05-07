// test file for deck implementation
// written by FyRel

#include "deck.h"
#include "riffle.h"
#include <stdio.h>
#include <assert.h>

// test function definitions
void test_addCard(void);
void test_removeCard(void);

int main(void) {

	// create a new deck
	Deck d = newStandardDeck();

	// show deck
	showDeck(d);

	// cut the deck
	Deck l = cutDeck(d, 26);

	// show both decks
	showDeck(l);
	showDeck(d);

	// free deck
	freeDeck(d);

	return 0;
}


































































/*
								SPACE
*/

























































































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

void test_removeCard(void) {
/*
	// CASE 1: attempt to remove a card from an empty deck
	Deck d = newEmptyDeck();
	//Card c = removeCard(d, 0);

	// CASE 2: remove the last card from the deck
	addCard(newCard('t', 0), d, 0);
	assert(deckSize(d) == 1);
	Card c = removeCard(d, 0);
	assert(deckSize(d) == 0);
	printCard(c);

	// CASE 3: remove all the cards from a standard deck from the bottom
	Deck fulldeck = newStandardDeck();
	int deck_size = deckSize(fulldeck);
	printf("deck_size = %d\n", deck_size);

	showDeck(fulldeck);

	for (int i = 0; i < deck_size; i++) {
		Card c = removeCard(fulldeck, -1);
		printCard(c);
		showDeck(fulldeck);
	}
	printf("\n");
*/
}







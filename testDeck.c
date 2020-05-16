// test file for deck implementation
// written by FyRel

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "deck.h"
//#include "random.h"


// test function definitions
void test_addCard(void);
void test_removeCard(void);
void shuffle_test(void);
void test_getCard(void);

int main(void) {

	test_getCard();


	return 0;
}



void test_getCard(void) {
	// attempt to get card from NULL deck
	Deck d = NULL;
	Card c = getCard(d, 0);
	assert(c == NULL);
	freeDeck(d);

	// get top card from an empty deck
	d = newEmptyDeck();
	c = getCard(d, 0);
	assert(c == NULL);

	// get bottom card from an empty deck
	d = newEmptyDeck();
	c = getCard(d, -1);
	assert(c == NULL);
	c = getCard(d, 5);
	assert(c == NULL);

	// get top card from a 1 card deck
	assert(deckSize(d) == 0);
	c = newCard(0, 0);
	addCard(c, d, 0);
	assert(deckSize(d) == 1);
	Card get_c = getCard(d, 0);
	assert(deckSize(d) == 1);
	assert(valueCard(c) == 0);
	assert(suitCard(c) == 0);
	freeDeck(d);

	// get pos 1 card from 3 card deck
	d = newEmptyDeck();
	addCard(newCard(0, 0), d, -1);
	addCard(newCard(0, 1), d, -1);
	addCard(newCard(0, 2), d, -1);
	assert(deckSize(d) == 3);
	c = getCard(d, 0);
	assert(suitCard(c) == 0);
	assert(valueCard(c) == 0);
	c = getCard(d, 1);
	assert(suitCard(c) == 0);
	assert(valueCard(c) == 1);
	c = getCard(d, 2);
	assert(suitCard(c) == 0);
	assert(valueCard(c) == 2);
	freeDeck(d);

	// get pos 8 card from testing deck
	d = newTestDeck();
	c = getCard(d, 8);
	assert(valueCard(c) == 8);
	assert(suitCard(c) == 0);
	assert(deckSize(d) == 40);

	// get top card from testing deck
	c = getCard(d, 0);
	assert(valueCard(c) == 0);
	assert(suitCard(c) == 0);


	// get bottom card from testing deck
	c = getCard(d, -1);
	assert(valueCard(c) == 9);
	assert(suitCard(c) == 3);

	free(d);
	printf("[getCard] all tests passed!!\n");
}


/*

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

	// CASE 1: attempt to remove a card from an empty deck
	Deck d = newEmptyDeck();
	//Card c = removeCard(d, 0);
	// CORRECT

	// CASE 2: remove the last card from the deck
	addCard(newCard(0, 0), d, 0);
	assert(deckSize(d) == 1);
	Card c = removeCard(d, 0);
	assert(deckSize(d) == 0);
	// CORRECT

	// CASE 3: remove all the cards from a standard deck from the bottom
	Deck fulldeck = newStandardDeck();
	int size = deckSize(fulldeck);
	printDeck(fulldeck);

	for (int i = 0; i < size; i++) {
		c = removeCard(fulldeck, 26);
		printDeck(fulldeck);
	}

	assert(deckSize(fulldeck) == 0);
	assert(fulldeck->top == NULL);
	assert(fulldeck->bottom == NULL);
	// CORRECT

}


*/




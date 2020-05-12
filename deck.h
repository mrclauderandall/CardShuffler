// interface for deck ADT
// written by J+C

#ifndef DECK_H
#define DECK_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct card *Card;
typedef struct deck *Deck;


/*
	testing stutus for each function:
		A 	Assumed functional. function is simply enough 
			to assume that it works well
		T   testing needed. function appears to work but has
			not been tested and could have errors
		F   functional. this function has been tested and 
			works well
*/




/*
	create a new card with the given suit and value
	note: avoid adding the same card to more than 
	one deck at a time
*/
Card newCard(char suit, int value);			// A

/*
	return a new card with the same 
	suit and value as card c
*/
Card copyCard(Card c);						// A

// return the value of card c
int valueCard(Card c);						// A

// return the suit of card c
int suitCard(Card c);						// A

// create a new empty deck
Deck newEmptyDeck(void);					// A

// return size of deck
int deckSize(Deck d);						// A

// create a new standard ordered deck
/*
	suits:
		0	hearts
		1	clubs
		2	diomonds
		3	spades

	values:
		2	0
		3	1
		4	2
		5	3
		6	4
		7	5
		8	6
		9	7
		10	8
		J	9
		Q	10
		K	11
		A   12
*/
Deck newStandardDeck(void);					// A

/*
	add a card to the deck in position pos
	e.g:
	0  -> insert on top of deck
	1  -> insert card under the current top card
	4  -> insert card under the current 4th card
	-1 -> insert card at the bottom of the deck
	if pos > size of deck, add card to the bottom
	of the deck
*/
void addCard(Card c, Deck d, int pos);		// A

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
Card removeCard(Deck d, int pos);			// T

/*
	create a new deck and copy all of
	cards from d into the new deck
*/
Deck copyDeck(Deck d);						// T

// print out entire deck to stdin
void printDeck(Deck d);						// A

// print a card
void printCard(Card c);						// A

// free all memory used for the deck
void freeDeck(Deck d);						// F

// free all memory used for a card
void freeCard(Card c);						// F

// check to see if two decks are the same
bool equivalentDecks(Deck d1, Deck d2);		// TESTING NEEDED

// check to see if two cards are the same
bool equivalentCards(Card c1, Card c2);		// TESTING NEEDED

// check if a deck is empty
bool deckIsEmpty(Deck d);					// TESTING NEEDED

/*
	search for and return the position of a card in a deck
	return -1 if the card is not in the deck
*/
int cardPosition(Deck d, Card c);			// TESTING NEEDED

/*
	perform a perfect riffle on a deck of cards
	alternating the card to be released from each
	deck. The order of deck d will revert to its 
	original order after 52 perfect riffles
*/
void rifflePerfect(Deck d);					// TESTING NEEDED

/*
	perform a human like riffle shuffle
*/
void riffleHuman(Deck d);					// TESTING NEEDED

/*
	cut the deck based on the given size. the 
	deck returned should be the size give and d
	should now be the remaining cards
*/
Deck cutDeck(Deck d, int size);				// TESTING NEEDED

/*
	shuffle the deck with perfect randomness
*/
void shuffle(Deck d);						// TESTING NEEDED

/*
	return the card at position pos in deck d
*/
Card getCard(Deck d, int pos);				// TESTING NEEDED

#endif






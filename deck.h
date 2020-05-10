// definitions of deck ADT
// written by FyRel

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define DECK_SIZE 52

typedef struct card *Card;
struct card {
	int value, suit;
	Card above, bellow;
};

typedef struct deck *Deck;
struct deck {
	Card top, bottom;
	int size;
};

/*
	create a new card with the given suit and value
	note: avoid adding the same card to more than 
	one deck at a time
*/
Card newCard(char suit, int value);

/*
	return a new card with the same 
	suit and value as card c
*/
Card copyCard(Card c);

// return the value of card c
int valueCard(Card c);

// return the suit of card c
int suitCard(Card c);

// create a new empty deck
Deck newEmptyDeck(void);

// return size of deck
int deckSize(Deck d);

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
Deck newStandardDeck(void);

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
void addCard(Card c, Deck d, int pos);

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
Card removeCard(Deck d, int pos);

/*
	create a new deck and copy all of
	cards from d into the new deck
*/
Deck copyDeck(Deck d);

// print out entire deck to stdin
void printDeck(Deck d);

// print a card
void printCard(Card c);

// free all memory used for the deck
void freeDeck(Deck d);

// free all memory used for a card
void freeCard(Card c);

// check to see if two decks are the same
bool equivalentDecks(Deck d1, Deck d2);

// check to see if two cards are the same
bool equivalentCards(Card c1, Card c2);

/*
	search for and return the position of a card in a deck
	return -1 if the card is not in the deck
*/
int cardPosition(Deck d, Card c);









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
	char suit;
	int value;
	Card above, bellow;
};

typedef struct deck *Deck;
struct deck {
	Card top, bottom;
	int size;
};

typedef struct ddeck *DoubleDeck;
struct ddeck {
	Deck left, right;
};

// create a new card with the given suit and value
Card newCard(char suit, int value);

// create a new empty deck
Deck newEmptyDeck(void);

// create a new standard ordered deck
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
Deck addCard(Card c, Deck d, int pos);

// remove and return the top card from the deck
Card removeTopCard(Deck d);

// remove and return the bottom card from the deck
Card removeBottomCard(Deck d);

// print out entire deck to stdin
void showDeck(Deck d);

// print a card
void printCard(Card c);

// free all memory used for the deck
void freeDeck(Deck d);

// check to see if two decks are the same
bool equivalentDecks(Deck d1, Deck d2);

// riffle shuffle the deck
Deck riffle(Deck d, int kind);

// cut the deck 
// size is the size of the left deck
DoubleDeck cutDeck(Deck d, int size);







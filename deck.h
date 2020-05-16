// interface for deck ADT
// written by J+C

#ifndef DECK_H
#define DECK_H

#include <stdlib.h>
#include <stdbool.h>


typedef struct card *Card;
typedef struct deck *Deck;


/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Card ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	create a new card with the given suit and value
	note: avoid adding the same card to more than 
	one deck at a time
*/
Card newCard(int suit, int value);

/*
	return a new card with the same 
	suit and value as card c
*/
Card copyCard(Card c);

/*
	return the suit or value of card c
*/	
int suitCard(Card c);
int valueCard(Card c);

/*
	free all memory used for a card
*/
void freeCard(Card c);

/*
	return the card at position pos in deck d
*/
Card getCard(Deck d, int pos);

/*
	insert card c into deck d at 
	position pos
*/
void addCard(Card c, Deck d, int pos);

/*
	remove the card in deck d at 
	position pos
*/
Card removeCard(Deck d, int pos);

/*
	search for and return the position of a card in a deck
	return -1 if the card is not in the deck
*/
int cardPosition(Deck d, Card c);

/*
	return true if cards c1 and c2 
	have the same suit and value
*/
bool equivalentCards(Card c1, Card c2);





/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ Deck ADT functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/*  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	create a new empty deck
*/
Deck newEmptyDeck(void);

/*
	free all memory used for the deck
	do nothing if deck d is a null pointer
*/
void freeDeck(Deck d);

/*
	return size of deck
*/
int deckSize(Deck d);

/*
	check if a deck is empty
*/
bool deckIsEmpty(Deck d);

/*
	create a new standard playing card deck
	deck is in New Deck Order
*/
Deck newStandardDeck(void);

/*
	check to see if two decks are the same
*/
bool equivalentDecks(Deck d1, Deck d2);

/*
	create a new deck and copy all of
	cards from d into the new deck in 
	the same order
*/
Deck copyDeck(Deck d);

/*
	cut the deck based on the given size. the 
	deck returned should be the size give and d
	should now be the remaining cards
*/
Deck cutDeck(Deck d, int size);

/*
	shuffle the deck with perfect randomness
*/
void shuffle(Deck d);





/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ printing and testing ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	print a standard card in the form 'VS'
	if c is a null pointer, print NULL
	function does not print a new line
*/
void printCard(Card c);

/* 
	print out an entire standard deck
	from top to bottom
	function does not print a new line
*/
void printDeck(Deck d);

/* 
	print cards with intager values and suits
*/
void printC(Card c);

/* 
	print the deck with intager values and suits
*/
void printD(Deck d);

/* 
	create a deck with 40 cards with 
	numerical ordered suits and values
	check notes for details
*/
Deck newTestDeck(void);





/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ riffle functions ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */
/* ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~  ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ */

/*
	perform a perfect riffle on a deck of cards
	alternating the card to be released from each
	deck. The order of deck d will revert to its 
	original order after 52 perfect riffles
*/
void rifflePerfect(Deck d);


/*
	perform a riffle shuffle emulating the 
	way a human riffle shuffles a deck of cards
*/
void riffleHuman(Deck d);


#endif



/*		NOTES:

	deck card positions are 0 indexed:
		top->0->1->2-> ... ->last card
		use pos = -1 to indicate bottom of deck

	standard deck suit/value keys:
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

	testing deck suit/value keys:
		suits:	0, 1, 2, 3
		values:	0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		order: 00, 01, 02, 03, ..., 37, 38, 39

*/



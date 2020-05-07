// definitions of deck ADT
// written by FyRel

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

// create a new empty deck
Deck newEmptyDeck(void);

// create a new standard ordered deck
Deck newStandardDeck(void);

// create a new card with the given suit and value
Card newCard(char suit, int value);

// add a card to the top of a deck
Deck addCard(Card c, Deck d);

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

// riffle shuffle the deck
Deck riffle(Deck d, int kind);

// cut the deck 
// size is the size of the left deck
DoubleDeck cutDeck(Deck d, int size);







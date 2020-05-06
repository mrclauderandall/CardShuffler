// implementation of cards

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



/*
ASSUMPTIONS

	1) the top card of a deck is the card on the top of the deck when 
	a deck of cards is faced down. This is the card that is dealt first
	in most standard card games such as poker, gofish

	2) when cutting a deck, most people hold the deck in such a way 
	that means they 'count' from bottom to an estimated half way

	3) when cutting a deck, the deck on the right is actually the original
	deck, while the deck on the left is originally empty, and one by one has
	cards from the right (original) deck added to it

	4) it is ok for the top and bottom card to be the same card in a deck 
	with only 1 card in it


NOTES

	1) card 0x is a 'nothing card' that should not appear





*/







// riffle function definitions 
// written by FyRel







typedef struct ddeck *DoubleDeck;
struct ddeck {
	Deck left, right;
};

/* 
	return the size of the left cut deck
	the returned value is a 'rough' / random
	value emulating how a human cuts a deck

	note: if called multiple times withing
	the time frame of 1 second, all instances
	will be the same value unless the input
	'a' is changed between instances. In 
	normal usage, a can be left as 0.
*/
int left_deck(int a);

// cut the deck 
// size is the size of the left deck
DoubleDeck cutDeck(Deck d, int size);
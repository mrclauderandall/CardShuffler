// riffle function definitions
// written by FyRel

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
int leftDeckSize(int a);

/*
	riffle shuffle a deck of cards
	kind:
		0 	perfect shuffle
		1	human like shuffle
*/
//void riffle(Deck d, int kind);
void rifflePerfect(Deck d);
void riffleHuman(Deck d);

/*
	cut the deck based on the given size. the 
	deck returned should be the size give and d
	should now be the remaining cards

	e.g:

original deck d before cutting:
TOP-> 2s 3s 4s 5s 6s 7s 8s 9s 10s Js Qs Ks As <-BOTTOM

$ left_deck = cutDeck(d, 5);

left_deck = TOP-> 2s 3s 4s 5s 6s <- BOTTOM
d = TOP-> 7s 8s 9s 10s Js Qs Ks As <-BOTTOM
*/
Deck cutDeck(Deck d, int size);

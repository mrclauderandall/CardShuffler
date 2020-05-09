test: testDeck.c deck.c riffle.c
	gcc -o test testDeck.c deck.c riffle.c random.c -I.

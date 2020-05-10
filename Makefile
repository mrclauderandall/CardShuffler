pook: pook.c deck.c table.c
	gcc -o pook pook.c deck.c table.c -I.
test: testDeck.c deck.c riffle.c
	gcc -o test testDeck.c deck.c riffle.c random.c -I.
handValue:
	gcc -o handValue deck.c handValue.c
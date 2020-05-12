pook: pook.c deck.c table.c
	gcc -o pook pook.c deck.c table.c -I.
test: testDeck.c deck.c
	gcc -o test testDeck.c deck.c -I.
handValue:
	gcc -o handValue deck.c handValue.c
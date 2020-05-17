pook: pook.c deck.c table.c
	gcc -o pook pook.c deck.c table.c -I.
testD: testDeck.c deck.c
	gcc -o testD testDeck.c deck.c -I.
handValue:
	gcc -o handValue deck.c handValue.c
testT: testTable.c table.c deck.c
	gcc -o testT testTable.c table.c deck.c -I

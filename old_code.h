/*

This file contains code that is no longer in use that we 
wish to save. This is not compilable code

*/


// code for testing the random number distrobution of 
// left_deck(int a);
int test[52] = {0};
int n = 0;
for (int i = 0; i < 10000; i++) {
	n = left_deck(i);
	test[n] = test[n] + 1;
}

for (int i = 0; i < 52; i++) {
	printf("card[%d] = %d\n", i, test[i]);
}


// test remove top card
	Card c;
	for (int i = 0; i < 53; i++) {
		// remove the top card
		c = removeTopCard(d);

		// print the top card
		printf("							removed card: ");
		printCard(c);
		printf("\n");

		// print the deck
		showDeck(d);

		// free the card
		free(c);
	}








	// old show card function
	int count = 0;
	while (c != NULL) {
		
		printCard(c);

		count++;

		if (count >= 13) {
			printf("\n");
			count = 0;
		}

		if (c == d->bottom) {
			break;
		} else {
			c = c->bellow;
		}
	}
	printf("..end of deck..\n\n");
	
	printf("from bottom to top:\n");

	c = d->bottom;

	count = 0;
	while (c != NULL) {
		
		printCard(c);

		count++;

		if (count >= 13) {
			printf("\n");
			count = 0;
		}

		if (c == d->top) {
			break;
		} else {
			c = c->above;
		}
	}
	printf("..end of deck..\n\n");




	// cut the deck with random size
	int size = left_deck(0);
	DoubleDeck dd = cutDeck(d, size);
	printf("\n\nTHE DECK HAS BEEN CUT\n\n");
	printf("left deck:\n");
	showDeck(dd->left);
	printf("\n\n\nright deck:\n");
	showDeck(dd->right);
	printf("\n\n\noriginal deck:	(should be the same as the right deck)\n");
	showDeck(d);





				insert_card = removeBottomCard(dd->left);
				insert_card->bellow = c;
				
				if (c == dd->right->top) {
					c->above = insert_card;
					dd->right->top = insert_card;

				} else {
					insert_card->above = c->above;
					c->above = insert_card;
					insert_card->above->bellow = insert_card;
				}





	// print the deck
	printf("original deck:\n");
	showDeck(d);

	// perfect riffle shuffle deck
	
	for (int i = 0; i < 9; i++) {
		printf("\nriffle shuffling deck:\n");
		d = riffle(d, 0);
		showDeck(d);
	}
	

	// show deck
	
	// show the deck
	printf("original deck: ");
	showDeck(d);
	printf("\n\n");
    
	// riffle deck 7 times and show deck after each riffle
	for (int i = 0; i < 53; i++) {
		printf("now starting riffle shuffle number %d\n", i);

		// riffle deck
    	riffle(d, 0);
    	
    	//show the deck riffled
    	printf("after riffle number %d:		d->size = %d\n", i, d->size);
    	showDeck(d);
    	printf("\n");
	}





	// old	

	// add card to the top of the deck
	if (d->top == NULL) {
		d->top = c;
		d->bottom = c;
	} else {
		d->top->above = c;
		d->top->above->bellow = d->top;
		d->top = d->top->above;
	}
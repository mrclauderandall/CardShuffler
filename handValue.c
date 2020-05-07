#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "string.h"
#include "deck.h"
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#define ACE   14
#define KING  13
#define QUEEN 12
#define JACK  11

#define SPADES   1
#define DIAMONDS 2
#define CLUBS    3
#define HEARTS   4

/*
struct {
    unsigned int Aces:   4;
    unsigned int Kings:  4;
    unsigned int Queens: 4;
    unsigned int Jacks:  4;
    unsigned int Ten:    4;
    unsigned int Nine:   4;
    unsigned int Eight:  4;
    unsigned int Seven:  4;
    unsigned int Six:    4;
    unsigned int Five:   4;
    unsigned int Four:   4;
    unsigned int Three:  4;
    unsigned int Two:    4;
}cardPairs = {0,0,0,0,0,0,0,0,0,0,0,0,0};
*/
/*
int r = value % 13;
int s = value / 13;
*/

u_int64_t cardPairs = 0x0000000000000000;


void printbits(u_int64_t number);

/*
2^((4*i)+j) where i = 0...12 (value of 2 to A) and j == 0..3 (suits)
*/

int main(int argc, char* argv[]) {

    Card c1 = newCard('d',14);
    Card c2 = newCard('c',2);
    Card c3 = newCard('c',14);
    Card c4 = newCard('h',7);
    Card c5 = newCard('d',11);
    Deck d1 = newEmptyDeck();
    addCard(c1, d1, 0);
    addCard(c2, d1, 1);
    addCard(c3, d1, 2);
    addCard(c4, d1, 3);
    addCard(c5, d1, 4);
    showDeck(d1);
    u_int64_t x = pow(2,51);
    printbits(x);
    /*
    int i = 1;
    while(i < argc) {

        printf("card %s\n", argv[i]);
        if (argv[i][0] == 'A' || argv[i][0] == 'K' || argv[i][0] == 'Q' || argv[i][0] == 'J'){

            printf("royal\n");

        } else {
            if (strlen(argv[i]) > 2) {

                printf("tenner\n");

            } else {

                printf("%d\n", argv[i][0] - '0');

            }
        }

        i++;



    }
    */
    return 0;

}
/*
int isFlush(Deck d1) {
    int i = 0;
    int diamonds = 0;
    int highD = 0;
    int hearts = 0;
    int highH = 0;
    int clubs = 0;
    int highC = 0;
    int spades = 0;
    int highS = 0;
    Card temp = d1->top;
    while (i < d1->size) {
        if (temp->suit == 'd') {
            diamonds++;
            if (highD < temp->value) {
                highD = temp->value;
            }
        } else if (temp->suit == 'h') {
            hearts++;
            if (highH < temp->value) {
                highH = temp->value;
            }

        } else if (temp->suit == 'c') {
            clubs++;
            if (highC < temp->value) {
                highC = temp->value;
            }
        } else if (temp->suit == 's') {
            spades++;
            if (highS < temp->value) {
                highS = temp->value;
            }
        }
        temp = temp->bellow;
        i++;
    }

    if (diamonds >= 5)
}
*/
void printbits(u_int64_t number){
    //loop counter
    int i = 0;
        /*
            A mask is used by bitwise AND to determine
            if a specific 1 or a 0 is present.
            Masks are used to select some bits
            (using 1s - which returns 1, if 1, and returns 0, if 0)
            or hide other bits
            (using 0s - which make everything zero).
            This starts with a 1 at the 31st (leftmost) position,
            followed by 31 zeros.
        */
    u_int64_t mask = 0x8000000000000000;

    //loop through the 32 bits
    for(i=63;i>=0;i--) {
            //printf("i=%i, mask=0x%x",i,mask);
            //determine if a 1 or 0 exists at each bit location
        if(0 != (number & mask)){
            printf("1");
        }
        else{
            printf("0");
        }
        //add a space for easy reading
        //if((56==i) || (48==i) || (40==i) || (32==i) || (24==i) || (16==i) || (8==i)){
        if (i%4 == 0) {
            printf(" ");
        }
        //shift bits in mask to the right by one bit
        mask = mask >> 1;
    }//end of for loop

    /*
    Display the unsigned integer.
    %u is the format character for unsigned integers.
    %d is for signed integers - use if you want to display negative numbers.
    Leave room for 8 extra spaces for hexadecimal numbers.
  */
    printf(" = 0x%.16llX = %lld \n", number, number);
}//end of function

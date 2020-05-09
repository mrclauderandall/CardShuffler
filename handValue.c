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

#define SPADES   0
#define DIAMONDS 1
#define CLUBS    2
#define HEARTS   3

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



int leastSignificantBit(uint64_t number);
void printbits(uint64_t number);
int isStraightFlush(uint64_t h);
int isFourOfAKind(uint64_t h);
/*
2^((4*i)+j) where i = 0...12 (value of 2 to A) and j == 0..3 (suits)
*/

int main(int argc, char* argv[]) {

    Card c1 = newCard(0,12);
    Card c2 = newCard(1,2);
    Card c3 = newCard(2,12);
    Card c4 = newCard(3,7);
    Card c5 = newCard(0,11);
    Deck d1 = newEmptyDeck();
    addCard(c1, d1, 0);
    addCard(c2, d1, 1);
    addCard(c3, d1, 2);
    addCard(c4, d1, 3);
    addCard(c5, d1, 4);
    showDeck(d1);
    uint64_t cardPairs = 0x0000000000000000;
    uint64_t AH = pow(2,49);
    uint64_t KH = pow(2,46);
    uint64_t QH = pow(2,17);
    uint64_t JH = pow(2,16);
    uint64_t TH = pow(2,14);
    uint64_t TS = pow(2,13);
    uint64_t NS = pow(2,12);
    cardPairs = cardPairs | NS | TS | AH | KH | QH | JH | TH;
    uint64_t logster = cardPairs & -cardPairs;
    printf("%llu\n", logster);
    int count = 0;
    while (logster > 1) {
        logster = logster/2;
        count++;
    }
    printf("%d\n", count);
    count = count -3;
    //uint64_t hh = (cardPairs>>(count)) & (cardPairs>>(count+4)) & (cardPairs>>(count+8)) & (cardPairs>>(count+12)) & (cardPairs>>(count+16));
    //uint64_t hh = (cardPairs) & (cardPairs>>(4)) & (cardPairs>>(8)) & (cardPairs>>(12)) & (cardPairs>>(16));
    //printf("%llu\n", hh);
    isStraightFlush(cardPairs);
    isFourOfAKind(cardPairs);
    printbits(cardPairs);
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

int isStraightFlush(u_int64_t h) {
    uint64_t AtoFiveS = 0x0001000000001111;
    uint64_t AtoFiveD = 0x0002000000002222;
    uint64_t AtoFiveC = 0x0004000000004444;
    uint64_t AtoFiveH = 0x0008000000008888;
    int AtoFiveFlag = 0;
    if (((h & AtoFiveS) == AtoFiveS) || ((h & AtoFiveD) == AtoFiveD) || ((h & AtoFiveC) == AtoFiveC) || ((h & AtoFiveH) == AtoFiveH)){
        AtoFiveFlag = 1;
    }


    uint64_t hh = (h) & (h>>(4)) & (h>>(8)) & (h>>(12)) & (h>>(16));
    if (hh > 0) {
        printf("OTHER STRAIGHT!\n");
        return 1;
    } else if (AtoFiveFlag == 1){
        printf("Straight Flush A to 5!\n");
        return 1;
    }
    return 0;
}

int isFourOfAKind(uint64_t h) {

    uint64_t mask = 0x0001111111111111;
    uint64_t hh = h & (h>>1) & (h>>2) & (h>>3) & mask;
    if (hh > 0) {
        printf("four of a kind!\n");
        return 1;
    }
    return 0;
}

int leastSignificantBit(uint64_t number) {
    int index = 0;

    while ((~number) & 1) {
        number >>= 1;
        index++;
    }
    return 1 << index;
}


void printbits(uint64_t number){
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
    uint64_t mask = 0x8000000000000000;

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

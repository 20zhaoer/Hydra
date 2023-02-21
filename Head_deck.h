#ifndef Head_deck_H_
#define Head_deck_H_
#include "Deck.h"

using namespace std;

class Head_deck: public Deck{
    static int headcount;
public:
    int head_num;
    Head_deck();
    Card * topCard();
    int isValid(Card *c);
};


#endif // Head_deck_H

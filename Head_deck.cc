#include <string>
#include <vector>
#include <ctime>
#include "Head_deck.h"
using namespace std;

Head_deck::Head_deck(){
    head_num = headcount;
    ++headcount;
}

Card * Head_deck::topCard(){
    if(isEmpty()) return nullptr;
    return deckofCards.back();
}
int Head_deck::headcount = 1;
int Head_deck::isValid(Card *c){//return 0 if not, 1 if >, 2 if ==
    if(c==nullptr) return 0;
    if(topCard()==nullptr) return 1;
    if(topCard()->getValue() > c->getValue()) return 1;
    else if(topCard()->getValue() == c->getValue()) return 2;
    else if(topCard()->getValue()==1) return 1; //ace case
    else return 0;
}

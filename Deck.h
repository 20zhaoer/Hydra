#ifndef Deck_H_
#define Deck_H_

#include <string>
#include <vector>
#include "Card.h"

using namespace std;

class Deck{
protected:
    vector <Card*> deckofCards;
    string type[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
public:
    Card* draw();
    int length();
    void put(Card *c);
    bool isEmpty();
    void shuffle();
    ~Deck();
};

#endif // Deck_H

#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Deck.h"
using namespace std;

Card* Deck::draw(){
    Card* temp = nullptr;
    if(!isEmpty()){
        temp = deckofCards.back();
        deckofCards.pop_back();
    }
    return temp;
}

int Deck::length(){return deckofCards.size();}

void Deck::put(Card *c){
    deckofCards.emplace_back(c);
}

bool Deck::isEmpty(){
    return deckofCards.empty();
}

void Deck::shuffle(){
    random_shuffle(deckofCards.begin(),deckofCards.end());
}

Deck::~Deck(){
    for(auto it = deckofCards.begin();it!=deckofCards.end();++it){
        delete (*it);
    }
    deckofCards.clear();
}

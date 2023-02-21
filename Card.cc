#include <string>
#include "Card.h"
using namespace std;

Card::Card(string suit, int value){
    this->suit = suit;
    this->value = value;
}

void Card::setValue(int value){
    this->value = value;
}

string Card::getName(){return type[value-1]+suit;}

int Card::getValue(){return value;}

string Card::getSuit(){return suit;}

void Card::setSuit(string s){this->suit = s;}

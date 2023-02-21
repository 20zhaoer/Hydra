#ifndef Card_H
#define Card_H

#include <string>

using namespace std;

class Card{
    string suit;
    int value;
    string type[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
public:
    Card(string suit, int value);
    void setValue(int value);
    string getName();
    int getValue();
    string getSuit();
    void setSuit(string s);
};

#endif // Card_H

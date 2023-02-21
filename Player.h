#ifndef Player_H_
#define Player_H_

#include "Deck.h"

using namespace std;

class Player{
    Deck draw_deck;
    Deck discard_deck;
    Card *reserve = nullptr;
    friend class Game;
public:
    bool isWin();
    void put_draw(Card *c);
    void put_discard(Card *c);
    Card* draw();
    int draw_length();
    int discard_length();
    ~Player();
};

#endif

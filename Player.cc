#include <string>
#include <vector>
#include <iostream>

#include "Player.h"

using namespace std;

bool Player::isWin(){
    //if a player has no card, he wins
    if(draw_deck.isEmpty()&&discard_deck.isEmpty()&&reserve==nullptr){
        return true;
    }
    return false;
}

void Player::put_draw(Card *c){
    draw_deck.put(c);
}

void Player::put_discard(Card *c){
    discard_deck.put(c);
}

Card* Player::draw(){
        //there's at least one card in player's hand
        //first if the draw_deck is not empty, draw from the draw deck
        if(!draw_deck.isEmpty()){
            return draw_deck.draw();
        }
        else if(!discard_deck.isEmpty()){
            //next if the draw_deck is empty, but the discard_deck is not
            //shuffle discard deck first, and put every card to the draw card, and then draw
            discard_deck.shuffle();
            while(!discard_deck.isEmpty()){
                Card * temp = discard_deck.draw();
                draw_deck.put(temp);
            }
            return draw_deck.draw();
        }
        else{
            //if both of them are empty, draw from reserve card.
            Card *temp = reserve;
            reserve = nullptr;
            return temp;
        }
}

int Player::draw_length(){ return draw_deck.length();}

int Player::discard_length(){ return discard_deck.length();}

Player::~Player(){
    delete reserve;
}

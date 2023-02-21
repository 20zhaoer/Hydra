#ifndef Game_H_
#define Game_H_
#include <vector>
#include <string>
class Head_deck;
class Player;
class Card;
using namespace std;

class Game{
    bool testmode;
    int num_player;
    int current_player=1;
    int num_head = 0;
    Card * current_card = nullptr;
    vector <Player*> p;
    vector <Head_deck*> h;
    string type[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    string suit[5] = {"S","D","H","C","J"};
public:
    Game(int n, bool test);
    void testing(Card * temp);
    void init(int n);
    void status(int inhand=0, int remaining=0, int reserve=0);
    void play();
    ~Game();

};

#endif

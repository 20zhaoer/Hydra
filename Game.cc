#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "Game.h"
#include "Head_deck.h"
#include "Player.h"
#include "Card.h"
using namespace std;

Game::Game(int n, bool test){
    testmode = test;
    init(n);
}

void Game::testing(Card * temp){
        while(true){
            cout<<"Card Value?"<<endl;
            string s;
            cin>>s;
            if(s=="Joker"){
                temp->setSuit("J");
                break;
            }
            int index = -1;
            for(int i = 0;i<13;++i){
                if(s==type[i]){
                    index = i;
                    break;
                }
            }
            if(!cin){
                if(cin.eof())return;
                cin.clear();
                cin.ignore();
                continue;
            }
            if(index>=0) temp->setValue(index+1);
            else{
                cout<< "Invalid value."<<endl;
                continue;
            }

            cout<<"Suit?"<<endl;
            cin>>s;
            if(s=="S"||s=="H"||s=="C"||s=="D") {
                temp->setSuit(s);
                break;
            }
            else{
                cout<<"Invalid suit."<<endl;
                continue;
            }
            if(!cin){
                if(cin.eof()) return;
                cin.clear();
                cin.ignore();
                continue;
            }
        }
    }

void Game::init(int n){
        num_player = n;
        for(int i =0;i<n;++i){
            p.emplace_back(new Player);
        }//add n player to the vector
        Deck d;
        for(int k = 0;k<num_player;++k){
            for(int i = 0;i<13;++i){
                for(int j = 0;j<4;++j){
                    d.put(new Card(suit[j],i+1));
                }
            }
            d.put(new Card("J",2)); d.put(new Card("J",2));
        }
        d.shuffle();
        //then distribute to each player 54 cards
        for(auto it = p.begin();it!=p.end();++it){
            for(int j = 0;j<54;++j){
                Card *temp = d.draw();
                (*it)->put_draw(temp);
            }
        }
        h.emplace_back(new Head_deck);
        current_card = p[0]->draw();
        if(testmode) testing(current_card);
        h[0]->put(current_card);
        current_card = nullptr;
        ++current_player;
    }


void Game::status(int inhand, int remaining, int reserve){
        cout<<"Heads: "<<endl;
        for(auto it = h.begin();it!=h.end();++it){
            if((*it)->topCard()!=nullptr){
                cout<<(*it)->head_num<<": "<<(*it)->topCard()->getName()<<" ("<<(*it)->length()<<")"<<endl;
            }
        }
        cout<<endl;
        cout<<"Players: "<<endl;
        int count = 1;
        if(inhand==0&&remaining==0&&reserve==0){
            for(auto it=p.begin();it!=p.end();++it){
                int dw_length = (*it)->draw_length(); int dis_length = (*it)->discard_length();
                cout<<"Player "<<count<<": "<< dw_length+dis_length<<" ("<<dw_length<<" draw, "<<dis_length<<" discard)"<<endl;
                ++count;
            }
        }
        else{
            for(auto it=p.begin();it!=p.end();++it){
                int dw_length = (*it)->draw_length(); int dis_length = (*it)->discard_length();
                if(current_player==count){
                    cout<<"Player "<<count<<": "<< dw_length+dis_length<<" ("<<dw_length<<" draw, "<<dis_length<<" discard)"
                    <<" + "<<inhand<<" in hand, "<<remaining<<" remaining, "<<reserve<<" in reserve"<<endl;
                }
                else cout<<"Player "<<count<<": "<< dw_length+dis_length<<" ("<<dw_length<<" draw, "<<dis_length<<" discard)"<<endl;
                ++count;
            }
        }
        cout<<endl;
}

void Game::play(){
        while(true){
            status();
            cout<<endl;
            cout<<"Player "<<current_player<<"'s turn "<<endl;
            cout<<endl;
            bool endTurn = false;
            Player * pl = p[current_player-1];
            for(int i = h.size();i>=1;--i){
                current_card = pl->draw();
                int isReserve = 0;
                if(pl->reserve!=nullptr) isReserve = 1;
                status(1,i-1,isReserve);
                if(testmode) testing(current_card);

                while(true){
                    if(current_card->getSuit()=="J"){
                        cout<<"Player "<<current_player<<", You are holding a "<<"Joker"<<". Your move?"<<endl;
                    }
                    else{
                        cout<<"Player "<<current_player<<", You are holding a "<< current_card->getName()<<". Your move?"<<endl;
                    }
                    int n;
                    cin>>n;
                    if(!cin){
                        if(cin.eof())return;
                        cin.clear();
                        cin.ignore();
                        continue;
                    }

                    if(n==0){ //swaping the reserve with current_card
                        Card *temp = current_card;
                        current_card = pl->reserve;
                        pl->reserve = temp;
                        if(current_card==nullptr) break;
                        else continue;
                    }

                    //check if the head number exist or not
                    bool isExist = false;
                    auto current_head = *(h.begin());
                    for(auto it = h.begin();it!=h.end();++it){
                        if((*it)->head_num==n){
                            isExist = true;
                            current_head = *it;
                            break;
                        }
                    }
                    if(!isExist){
                        cout<<"The head doesn't exist!"<<endl;
                        continue;
                    }
                    //set the joker's value
                    if(current_card->getSuit()=="J"){
                        cout<< "Joker value?"<<endl;
                        string s;
                        cin>>s;
                        if(cin.eof())return;
                        int index = -1;
                        for(int i = 0;i<13;++i){
                            if(s==type[i]){
                                index = i;
                                break;
                            }
                        }
                        if(index>=0) current_card->setValue(index+1);
                        else{
                            cout<< "Invalid value."<<endl;
                            continue;
                        }
                    }

                    //
                    int valid = current_head->isValid(current_card);
                    if(valid ==1){//smaller case
                        current_head->put(current_card);
                        current_card = nullptr;
                        break;
                    }
                    if(valid==2){//equal case
                        current_head->put(current_card);
                        current_card = nullptr;
                        endTurn = true;
                        break;
                    }

                    if(valid==0){
                        //check if it's the case to cut off a head
                        if(n==(*h.begin())->head_num){ // if it is the first active head
                            bool iscut = true;
                            for(auto it = h.begin();it!=h.end();++it){
                                if((*it)->isValid(current_card)!=0){
                                    iscut = false;
                                }
                            }
                            if(iscut){ //if yes
                                pl->put_discard(current_card); //put the play card into discard
                                current_card = nullptr;

                                if(pl->reserve!=nullptr){ //if there's reserve, put it into the draw deck
                                    pl->put_draw(pl->reserve);
                                    pl->reserve = nullptr;
                                }
                                while(!current_head->isEmpty()){ //put every card in the head into the discard
                                    pl->put_discard(current_head->draw());
                                }
                                //delete the current head
                                delete current_head;
                                h.erase(h.begin());
                                current_card = pl->draw();
                                if(testmode) testing(current_card);
                                if(current_card->getSuit()=="J") current_card->setValue(2);
                                h.emplace_back(new Head_deck); h.back()->put(current_card);
                                current_card = nullptr;

                                current_card = pl->draw();
                                if(testmode) testing(current_card);
                                if(current_card->getSuit()=="J") current_card->setValue(2);
                                h.emplace_back(new Head_deck); h.back()->put(current_card);
                                current_card = nullptr;

                                endTurn = true;
                                break;

                            }
                            else{
                                cout<<"Invalid to put on head "<<n<<endl;
                                continue;
                            }

                        }
                        else{
                            cout<<"Invalid to put on head "<<n<<endl;
                            continue;
                        }
                    }

                }

                if(pl->isWin()){
                    cout<<"Player "<<current_player<<" wins!"<<endl;
                    return;
                }

                if(endTurn){
                    break;
                }
            }
            //at the end of a turn
            //put the reserve back if there is a reserve card
            if(pl->reserve!=nullptr){
                pl->put_draw(pl->reserve);
                pl->reserve = nullptr;
            }
            ++current_player;
            if(current_player>num_player) current_player = current_player%num_player;
    }
}

Game::~Game(){
    delete current_card;
    for(auto it = p.begin();it!=p.end();++it){
        delete (*it);
    }
    for(auto it = h.begin();it!=h.end();++it){
        delete (*it);
    }
}

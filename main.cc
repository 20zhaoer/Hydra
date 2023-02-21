#include <string>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include "Game.h"

int main(int argc, char *argv[]){
    bool test = false;
    unsigned int sd = time(NULL);
    if(argc==2){
        string argv1 = argv[1];
        if(argv1=="-testing"){
            test = true;
        }
        else{
            cout<<"usage: "<< argv[0]<< " -testing  Or "<<argv[0]<<" -seed (unsigned int)"<<endl;
            return 0;
        }
    }
    else if(argc==3){
        string argv1 = argv[1];
        if(argv1 =="-seed"){
            istringstream s{argv[2]};
            s>> sd;
        }
        else{
            cout<<"usage: "<< argv[0]<< " -testing  Or "<<argv[0]<<" -seed (unsigned int)"<<endl;
            return 0;
        }
    }
    int players=0;
    cout<< "How many players?"<<endl;
    cin>>players;
    if(players<=1){
        cout<<"There must be at least 2 players."<<endl;
        return 0;
    }
    srand(sd);
    Game g = Game(players,test);
    g.play();

}

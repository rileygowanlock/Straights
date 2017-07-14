#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {

public:
    Human(Deck* d, int playerNum); //Human constructor
    ~Human(); //Human destructor
    void play(Card& c) override; //plays card c
    void discard(Card& c) override; //discards card c
    bool isHuman() override; //returns if human (true)

};


#endif //HUMAN_H

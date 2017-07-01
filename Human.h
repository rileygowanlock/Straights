#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"

class Human : public Player {

public:
    //Human(int playerNum);
    Human(Deck* d, int playerNum);
    ~Human();
    //void play(Deck &d, Card* c) override;
    //void discard(Card* c) override;
    void play(Card& c) override;
    void discard(Card& c) override;
    bool isHuman() override;
    void rageQuit();
};


#endif //HUMAN_H

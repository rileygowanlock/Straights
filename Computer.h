#ifndef COMPUTER_H
#define COMPUTER_H

class Computer : public Player {

public:
    Computer(Deck* d, int playerNum); //Computer constructor
    ~Computer(); //Computer destructor
    Card* play() override; //plays first legal card and returns card played
    Card* discard() override; //discards first card and returns card discarded
    bool isHuman() override; //returns if human (false)
};

#endif //COMPUTER_H


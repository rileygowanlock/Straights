#ifndef COMPUTER_H
#define COMPUTER_H

class Computer : public Player {

public:
    //Computer(int playerNum);
    Computer(Deck* d, int playerNum);
    ~Computer();
    //destructor
    void play() override;
    void discard() override;
    bool isHuman() override;
};

#endif //COMPUTER_H

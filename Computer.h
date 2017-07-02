#ifndef COMPUTER_H
#define COMPUTER_H

class Computer : public Player {

public:
    Computer(Deck* d, int playerNum);
    ~Computer();
    void play() override;
    void discard() override;
    bool isHuman() override;
};

#endif //COMPUTER_H

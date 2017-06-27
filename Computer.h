#ifndef COMPUTER_H
#define COMPUTER_H

class Computer : public Player {

public:
    Computer(int playerNum);
    Computer(Deck &d, int playerNum);
    //destructor
    void play(Deck &d) override;
    void discard() override;
};

#endif //COMPUTER_H

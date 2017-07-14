#ifndef STRAIGHTS_CONTROLLER_H
#define STRAIGHTS_CONTROLLER_H
#include "Model.h"
#include "Command.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
#include <string>
#include <iostream>
using std::string;

class Controller {
private:
    Model* model_; //model instance
    Card* card_;
public:
    Controller(Model* model);
    void invitePlayers(char playerType, int playerNum); //choose human or computer player
    void playRound(int playerNum);
    int newGame(std::vector<std::string> playerType, int seed);
    int newRound();
    Command::Type gamePlay(Card* card, int playerNum);
    Card* getCard();
    int index(int playerNum);
    Player* getPlayers(int playerNum);
    void startNotify(int playerNum);
    void shuffleDeck();
    void updatePlayers(int playerNum);
};

#endif //STRAIGHTS_CONTROLLER_H

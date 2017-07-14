#ifndef STRAIGHTS_CONTROLLER_H
#define STRAIGHTS_CONTROLLER_H
#include "Model.h"
#include "Command.h"

class Controller {
private:
    Model* model_; //model instance
    Card* card_;
public:
    Controller(Model* model);
    void invitePlayers(char playerType, int playerNum); //choose human or computer player
    void playRound(int playerNum);
    //bool gamePlay(Command &command, Player* player); //directs logic based on human's commands
    int newGame(std::vector<std::string> playerType, int seed);
    int newRound();
    Command::Type gamePlay(Card* card, int playerNum);
    Card* getCard();
};

#endif //STRAIGHTS_CONTROLLER_H

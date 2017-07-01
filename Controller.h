#ifndef STRAIGHTS_CONTROLLER_H
#define STRAIGHTS_CONTROLLER_H
#include "Model.h"
#include "Command.h"

class Controller {
private:
    Model* model_;
public:
    // queries user input
    // for each command updates model and view with data
    Controller(Model* model);
    void run();
    void invitePlayers(char playerType, int playerNum);
    //void gamePlay (Command::Type &command, Player* player, Card &card);
    bool gamePlay (Command &command, Player* player);
    int newGame();
};

#endif //STRAIGHTS_CONTROLLER_H

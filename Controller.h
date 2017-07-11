#ifndef STRAIGHTS_CONTROLLER_H
#define STRAIGHTS_CONTROLLER_H
#include "Model.h"
#include "Command.h"

class Controller {
private:
    Model* model_; //model instance
public:
    Controller(Model* model);
    void invitePlayers(char playerType, int playerNum); //choose human or computer player
    bool gamePlay(Command &command, Player*& player); //directs logic based on human's commands
    void newGame(std::vector<std::string> playerType, int seed);
};

#endif //STRAIGHTS_CONTROLLER_H

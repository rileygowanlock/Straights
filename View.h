#ifndef STRAIGHTS_VIEW_H
#define STRAIGHTS_VIEW_H
#include <string>
#include "Command.h"
#include "Model.h"
#include "Controller.h"
using std::string;

class View {
private:
    Model* model_;
    Controller* controller_;
public:
    View(Model* model, Controller* controller);
    void invitePlayers(int playerNum);
    void run();
    void play (Player *player, Card &card, bool legal);
    void discard (Player *player, Card &card, bool legal);
    Command getCommand();
    void update(Command::Type &command, Player* player, Card &card, bool isLegal);
};

#endif //STRAIGHTS_VIEW_H

#ifndef STRAIGHTS_VIEW_H
#define STRAIGHTS_VIEW_H
#include <string>
#include "Command.h"
#include "Model.h"
using std::string;

class View {
private:
    Model* model_;
public:
    View(Model* model);
    void invitePlayers(int playerNum);
    void run();
    Command getCommand();
};

#endif //STRAIGHTS_VIEW_H

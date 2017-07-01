#ifndef STRAIGHTS_VIEW_H
#define STRAIGHTS_VIEW_H
#include <string>
#include "Command.h"
using std::string;

class View {
public:
    void invitePlayers(int playerNum);
    Command getCommand();
};

#endif //STRAIGHTS_VIEW_H

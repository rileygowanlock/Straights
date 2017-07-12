#ifndef OBSERVER_H
#define OBSERVER_H
#include "Command.h"
#include "Player.h"
#include <gtkmm/button.h>
#include <gtkmm/window.h>

class Observer {
public:
    //virtual void update(Command::Type &command, Player* player, Card &card, bool isLegal) = 0;
    virtual void update(Command::Type &command, int playerNum, Card &card, bool isLegal) = 0;
    virtual void update(Player* player) = 0;
    
};


#endif //OBSERVER_H


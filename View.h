#ifndef STRAIGHTS_VIEW_H
#define STRAIGHTS_VIEW_H
#include <string>
#include "Command.h"
#include "Model.h"
#include "Controller.h"
#include "Observer.h"
#include <gtkmm/button.h>
#include <gtkmm/window.h>
using std::string;

class View : public Observer {
//private:
protected:
    Model* model_;
    Controller* controller_;
    int startPlayer_;
public:
    View(Model* model, Controller* controller);
    void invitePlayers(int playerNum);
    virtual void run();
    void play (Player *player, Card &card, bool legal);
    void human(int playerNum);
    void computer(int playerNum);
    void discard (Player *player, Card &card, bool legal);
    int playRound(int playerNum, int startPlayer);
    int endRound();
    void newGame();
    Command getCommand();
    virtual void update(Player* player);
    virtual void update(Command::Type &command, Player* player, Card &card, bool isLegal);
};

#endif //STRAIGHTS_VIEW_H

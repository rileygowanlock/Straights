#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"

class Subject {
private:
    vector <Observer*> observers_; //vector of subject's observers

//protected:
//    void notify(Player* player);
//    void notify(Command::Type &command, Player* player, Card &card, bool isLegal); //notifies each observer of an update

public:   
    ~Subject (); 
    void subscribe(Observer* observer); //add observer to subject's observer list
    void unsubscribe(Observer* observer); //remove observer from subject's observer list
    void notify(Player* player);
    //void notify(Command::Type &command, Player* player, Card &card, bool isLegal); //notifies each observer of an update
    void notify(Command::Type &command, int playerNum, Card &card, bool isLegal); //notifies each observer of an update
};


#endif //SUBJECT_H


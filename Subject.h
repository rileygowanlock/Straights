#ifndef SUBJECT_H
#define SUBJECT_H
#include "Observer.h"

class Subject {
private:
    vector <Observer*> observers_;

protected:
    void notify(Command::Type &command, Player* player, Card &card, bool isLegal);

public:    
    void subscribe(Observer* observer);
    void unsubscribe(Observer* observer);
};


#endif //SUBJECT_H


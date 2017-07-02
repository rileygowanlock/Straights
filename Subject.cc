#include "Subject.h"
#include <iostream>

//deletes all observers
Subject::~Subject() {
    for (auto it:observers_) {
        delete it;
    }
    observers_.resize(0);

}

//add observer to subject's observer list
void Subject::subscribe(Observer* observer) {
    observers_.push_back(observer);
}

//remove observer from subject's observer list
void Subject::unsubscribe(Observer* observer) {
    observers_.push_back(observer);
}

//notifies each observer of an update
void Subject::notify(Command::Type &command, Player* player, Card &card, bool isLegal) {
    for (auto it:observers_)  {
        (*it).update(command, player, card, isLegal);
    }

}

#include "Subject.h"
#include <iostream>

Subject::~Subject() {
    for (auto it:observers_) {
        delete it;
    }
    observers_.resize(0);

}

void Subject::subscribe(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::unsubscribe(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::notify(Command::Type &command, Player* player, Card &card, bool isLegal) {
    for (auto it:observers_)  {
        std::cout << std::to_string(observers_.size());
        (*it).update(command, player, card, isLegal);
    }

}

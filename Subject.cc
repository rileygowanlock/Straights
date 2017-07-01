#include "Subject.h"

void Subject::subscribe(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::unsubscribe(Observer* observer) {
    observers_.push_back(observer);
}

void Subject::notify(Command::Type &command, Player* player, Card &card, bool isLegal) {
    for (auto it:observers_)  {
        (*it).update(command, player, card, isLegal);
    }

}

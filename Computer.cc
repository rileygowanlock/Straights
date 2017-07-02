#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Computer.h"
#include <vector>
using std::vector;

//Computer::Computer(int playerNum) {};

Computer::Computer(Deck* d, int playerNum) : Player(d, playerNum) {

}

Computer::~Computer() {
//    for (auto it:hand_) {
//        delete it;
//    }
//
//    for (auto it2:discard_) {
//        delete it2;
//    }
//
//    hand_.resize(0);
//    discard_.resize(0);
}

void Computer::play() {
    Deck* d = getDeck();
    vector<Card*> leg = legalPlay();
    
    Card* c = leg[0];
    d->addPlayed(c);
 
    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() && *it!=c) {
        it++;
    }

    if(it != hand_.end()) {
        hand_.erase(it);
    }
}

void Computer::discard() {
    Card* c = hand_[0];
    discard_.push_back(c);

    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() && *it!=c) {
        it++;
    } 

    if(it != hand_.end())
        hand_.erase(it);
}

bool Computer::isHuman() {
    return false;
}

#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include <vector>
using std::vector;

//Human::Human(int playerNum) {}

Human::Human(Deck* d, int playerNum) : Player(d, playerNum) {
    score_ = 0;
}

Human::~Human() {
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

/*void Human::play(Deck &d, Card* c) {
    d.addPlayed(c);
    
    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() && *it!=c) {
        it++;
    }

    if(it != hand_.end())
        hand_.erase(it);
}

void Human::discard(Card* c) {
    discard_.push_back(c);

    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() && *it!=c) {
        it++;
    } 
    
    if(it != hand_.end())
       hand_.erase(it);
}*/

void Human::play(Card& c) {

    Deck* d = getDeck();
   
    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() ) {
	if ((*it)->suit().suit() == c.suit().suit() && (*it)->rank().rank() == c.rank().rank()) break;
        it++;
    }

    if(it != hand_.end()) {
	d->addPlayed(*it);
        hand_.erase(it);
    }

}

void Human::discard(Card& c) {

    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() ) {
	if ((*it)->suit().suit() == c.suit().suit() && (*it)->rank().rank() == c.rank().rank()) break;
        it++;
    }
    
    if(it != hand_.end()) {
        discard_.push_back(*it);       
        hand_.erase(it);
    }
}

bool Human::isHuman() {
    return true;
}



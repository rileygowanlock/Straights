#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Human.h"
#include "Computer.h"
#include <vector>
using std::vector;

Human::Human(Deck* d, int playerNum) : Player(d, playerNum) {
}

Human::~Human() {

}

//plays card c
void Human::play(Card& c) {

    Deck* d = getDeck();
   
    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() ) { //iterates through hand
	if ((*it)->suit().suit() == c.suit().suit() && (*it)->rank().rank() == c.rank().rank()) break; //checks if c is a card in hand 
        it++;
    }

    if(it != hand_.end()) { //if c is found in hand
	d->addPlayed(*it); //adds card to player's played vector
        hand_.erase(it); //removes from hand
    }

}

//discards card c
void Human::discard(Card& c) {

    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() ) { //iterates through hand
	if ((*it)->suit().suit() == c.suit().suit() && (*it)->rank().rank() == c.rank().rank()) break; //checks if c is a card in hand 
        it++;
    }
    
    if(it != hand_.end()) { //if c is found in hand
        discard_.push_back(*it); //adds card to player's discard pile  
        hand_.erase(it); //removes from hand
    }
}

//returns if human (true)
bool Human::isHuman() {
    return true;
}



#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Computer.h"
#include <vector>
using std::vector;

//Computer constructor
Computer::Computer(Deck* d, int playerNum) : Player(d, playerNum) {

}

//Computer destructor
Computer::~Computer() {
}

//plays first legal card and returns card played
Card* Computer::play() {
    Deck* d = getDeck();
    vector<Card*> leg = legalPlay(); //all legal cards
    
    Card* c = leg[0]; //first legal play
    d->addPlayed(c); //play card c
 
    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() && *it!=c) { //iterates through hand
        it++;
    }

    if(it != hand_.end()) {
        hand_.erase(it); //erase first legal card from hand
    }
    return c;
}

//discards first card and returns card discarded
Card* Computer::discard() {
	std::cout<<"COMPUTER::discard "<<*(hand_[0])<<std::endl;
    Card* c = hand_[0]; //first card in hand 
    discard_.push_back(c); //add c to discard

    vector<Card*>::iterator it;
    it = hand_.begin();
    while (it!=hand_.end() && *it!=c) { //iterates through hand
        it++;
    } 

    if(it != hand_.end())
        hand_.erase(it); //erase first card from hand
    return c;
}

//returns if human (false)
bool Computer::isHuman() {
    return false;
}

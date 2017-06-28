#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Human.h"
#include <vector>
using std::vector;

/*Human::Human(int playerNum) {
}*/

Human::Human(Deck &d, int playerNum) : Player(d, playerNum) {

}

void Human::play(Deck &d, Card* c) {
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
}

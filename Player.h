#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Deck.h"
#include <vector>
using std::vector;

class Player {
private:
    int playerNum_;

protected:
    vector<Card*> hand_;
    vector<Card*> discard_;

public:
    // added this to construct player before call to deck
    // addHand() method?
    //Player(int playerNum);
    Player(Deck &d, int playerNum);
    //destructor
    int score();
    //virtual void play(Deck &d) = 0;
    //virtual void discard() = 0;
    //virtual void play(Deck &d, Card *c);
    virtual void play(Deck &d, Card &c);
    virtual void play(Deck &d);
    //virtual void discard(Card *c);
    virtual void discard(Card &c); 
    virtual void discard();
    void addHand(vector<Card*> cards);
    vector<Card*> legalPlay (vector<vector<Card*>> &played);
    void printHand(); //FOR TEST PURPOSES
};

#endif //PLAYER_H

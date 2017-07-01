#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Deck.h"
#include <vector>
using std::vector;

class Player {
private:
    int playerNum_;
    Deck* deck_;

protected:
    vector<Card*> hand_;
    vector<Card*> discard_;

public:
    // added this to construct player before call to deck
    // addHand() method?
    //Player(int playerNum);
    Player(Deck* d, int playerNum);
    Deck* getDeck();
    //destructor
    int score();
    //virtual void play(Deck &d) = 0;
    //virtual void discard() = 0;
    vector<Card*> getHand();
    vector<Card*> getDiscard();
    //virtual void play(Deck &d, Card *c);
    //virtual void play(Deck &d, Card &c);
    virtual void play(Card& c);
    virtual bool isHuman();
    bool isStartPlayer();
    virtual void play();
    //virtual void discard(Card *c);
    virtual void discard(Card& c);
    virtual void discard();
    void addHand(vector<Card*> cards);
    vector<Card*> legalPlay ();
    void printHand(); //FOR TEST PURPOSES
    int playerNum();
};

#endif //PLAYER_H

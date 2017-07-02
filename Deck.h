#ifndef STRAIGHTS_DECK_H
#define STRAIGHTS_DECK_H

#include "Card.h"
#include <vector>
using std::vector;

class Deck {
private:
    vector<Card*> cards_; //holds all 52 cards of a deck 
    vector<vector<Card*>> played_; //stores cards already played
public:
    Deck(); //create deck
    ~Deck(); //destroy deck
    vector<vector<Card*>> played(); //returns played cards
    void print(); //prints deck in rows of 13 cards
    Card* getCard(int pos); //retrieves a card based on position in deck
    void addPlayed(Card* card); //add card to vector of played_ cards
    void shuffle(); //shuffle deck
    void removePlayed();
};

#endif //STRAIGHTS_DECK_H

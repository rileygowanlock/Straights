#ifndef STRAIGHTS_DECK_H
#define STRAIGHTS_DECK_H

#include "Card.h"
#include <vector>
using std::vector;

class Deck {
private:
    vector<Card*> cards_;
    vector<vector<Card*>> played_;
public:
    Deck();
    vector<vector<Card*>> played();
    void print();
    Card* getCard(int pos);
    void addPlayed(Card* card);
    void shuffle();
};

#endif //STRAIGHTS_DECK_H

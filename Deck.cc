#include "Deck.h"
#include "Card.h"
#include <vector>
#include <random>
#include <iostream>
using std::vector;
using std::string;
using std::mt19937;

int seed = 0;

Deck::Deck() {
    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++) {
            Card::Suit suit (i);
            Card::Rank rank (j);
            Card* card = new Card (rank, suit);
            cards_.push_back(card);
        }
    }
    for (int i=0; i<4; i++) {
        vector<Card*> card;
        card.resize(13);
        played_.push_back(card);
    }
}
vector<vector<Card*>> Deck::played() {
    return played_;
}
void Deck::print() {
    for (int i=0; i<cards_.size(); i++) {
        std::cout << *cards_[i] << std::endl;
    }
}
// for testing
Card* Deck::getCard(int pos) {
    return cards_[pos];
}
void Deck::addPlayed(Card* card) {
    int suit = card->suit().suit();
    int rank = card->rank().rank();
    played_[suit][rank] = card;
}
void Deck::shuffle() {
    static mt19937 rng(seed);
    int n = 52;

    while ( n > 1 ) {
        int k = (int) (rng() % n);
        --n;
        Card *c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    } // while
}


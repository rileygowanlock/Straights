#include "Deck.h"
#include "Card.h"
#include <vector>
#include <random>
#include <iostream>
using std::vector;
using std::string;
using std::mt19937;

int seed = 0;

//create deck
Deck::Deck() {
    //create 52 cards and store in order
    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++) {
            Card::Suit suit (i);
            Card::Rank rank (j);
            Card* card = new Card (rank, suit);
            cards_.push_back(card);
        }
    }
    //create a 4x13 2D vector of nullptrs
    for (int i=0; i<4; i++) {
        vector<Card*> card;
        card.resize(13);
        played_.push_back(card);
    }
}

//destroy deck
Deck::~Deck() {
        //delete each card in cards_ vector
//    for (auto it:cards_) {
//        delete it;
//    }

//      //delete each card in played_ vector
//    for(auto i1 = played_.begin(); i1 != played_.end(); i1++) {
//        for(auto i2 = i1->begin(); i2 != i1->end(); i2++) {
//            delete *i2;
//	}
//    }
//
//    cards_.resize(0);
//    played_.resize(0);
}

//return played cards
vector<vector<Card*>> Deck::played() {
    return played_;
}

//print deck in rows of 13 cards
void Deck::print() {
    for (int i=0; i<cards_.size(); i++) {
        std::cout << *cards_[i] << " ";
        if ((i+1)%13==0) {
            std::cout << "\n";
        }
    }
}

//retrieve a card based on position in deck
Card* Deck::getCard(int pos) {
    return cards_[pos];
}

//add card to vector of played_ cards
void Deck::addPlayed(Card* card) {
    int suit = card->suit().suit();
    int rank = card->rank().rank();
    played_[suit][rank] = card;
}

//shuffle deck
void Deck::shuffle() {
    static mt19937 rng(seed); // create random number using seed value
    int n = 52;

    while ( n > 1 ) {
        int k = (int) (rng() % n);
        --n;
        Card *c = cards_[n];
        cards_[n] = cards_[k];
        cards_[k] = c;
    } // while
}

void Deck::removePlayed() {
    vector<vector<Card*>> temp;
    for (int i=0; i<4; i++) {
        vector<Card*> card;
        card.resize(13);
        temp.push_back(card);
    }
    played_ = temp;
}


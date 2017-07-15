#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Computer.h"
#include <vector>
using std::vector;

//Player constructor
Player::Player(Deck* d, int playerNum): playerNum_(playerNum), deck_(d) {
    updateHand();
    score_ = 0;
}

//Player destructor
Player::~Player() {}

//returns legal plays of player based on current hand
vector<Card*> Player::legalPlay () {
    vector<vector<Card*>> played = deck_->played(); //all cards that are already played
    vector<Card*> legal; //vector to hold legal cards
    if (played[3][6] == nullptr) { //if (start) player has 7S, return 7S
        for (auto it:hand_) {
            int suit = it->suit().suit();
            int rank = it->rank().rank();
            if (rank == 6 && suit == 3) {
                legal.push_back(it);
            }
        }
        return legal;
    }
    for (auto it:hand_)  { // iterate through hand
        int suit = it->suit().suit();
        int rank = it->rank().rank();

        if (rank == 6) { //add any 7's to legal
            legal.push_back(it);
        }
        else if (rank!=12 && played[suit][rank+1] != nullptr) { //checks if card of 1 higher rank (and same suit) is played
            legal.push_back(it);
        }
        else if (rank!=0 && played[suit][rank-1] != nullptr) { //checks if card of 1 lower rank (and same suit) is played
            legal.push_back(it);
        }
    }
    return legal;
}

//returns sum of ranks of all discards
int Player::score() {
  int score = 0;
  for (auto it:discard_) {
    score += it->rank().rank() + 1;
  }
  return score;
}

// returns last stored score + sum of ranks of all discards and updates score_
void Player::updateScore() {
    score_ += score();
}

//returns player's current score (score_)
int Player::getScore() {
    return score_;
}

void Player::addScore(int num) {
    score_ = num;
}

//returns if player is human
bool Player::isHuman(){
    return false;
}

//returns whether player is the start player
bool Player::isStartPlayer() {
    for (int i=0; i<13; i++) {
        if (hand_[i]->suit().suit()==3 && hand_[i]->rank().rank()==6) {
            return true;
        }
    }
    return false;
}

Card* Player::play() {}

void Player::play(Card& c) { }

Card* Player::discard() {}

void Player::discard(Card& c) { }

//sets player's hand
void Player::updateHand() {
    hand_.clear();
    for (int i=0; i<13; i++) {
        hand_.push_back(deck_->getCard(i+playerNum_*13));
    }
}

//Prints hand - FOR TEST PURPOSES
void Player::printHand() {
    std::cout<<"Hand: "<<std::endl;
    for(auto it: hand_) {
      std::cout<<*it<< " ";
    }
    std::cout<<std::endl;
}

//returns vector of cards remaining in player's hand (hand_)
vector<Card*> Player::getHand() {
    return hand_;
}

//returns vector of cards player has discarded
vector<Card*> Player::getDiscard() {
    return discard_;
}

//returns player's number (position in player array)
int Player::playerNum() {
    return playerNum_;
}

//returns game's deck (deck_)
Deck* Player::getDeck() {
    return deck_;
}

//removes all cards in player's discard pile
void Player::resetDiscard() {
    discard_.clear();
}

//CLI ragequit 
void Player::rageQuit() {
    std::cout<<"Player "<<playerNum_+1<<" ragequits. A computer will now take over."<<std::endl;
}

void Player::setDiscard(vector<Card*> discard) {
    discard_=discard;
}

void Player::setHand(vector<Card*> hand) {
    hand_=hand;
}

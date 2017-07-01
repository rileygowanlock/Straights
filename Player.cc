#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include <vector>
using std::vector;

/*Player::Player(int playerNum) {
    playerNum_ = playerNum;
}*/

Player::Player(Deck &d, int playerNum): playerNum_(playerNum) {
   for (int i=0; i<13; i++) {
       hand_.push_back(d.getCard(i+playerNum_*13));
    }
   /*for (auto it:hand_) {
	std::cout<<*it<<std::endl;
   }*/ // prints hand
}

vector<Card*> Player::legalPlay () {
    vector<vector<Card*>> played = deck_->played();
    vector<Card*> legal;
    if (played.size()==0) {
        Card::Suit suit (3); //SPADE?
        Card::Rank rank (6); //SEVEN?
        Card* card = new Card (rank, suit);
        legal.push_back(card);
    }
    for (auto it:hand_)  {
	int suit = it->suit().suit();
	int rank = it->rank().rank();

	if (rank == 6) {
	    legal.push_back(it);
	}
	else if (rank!=12 && played[suit][rank+1] != nullptr) {
	    legal.push_back(it);
	}
	else if (rank!=0 && played[suit][rank-1] != nullptr) {
	    legal.push_back(it);
	}
    }
    return legal;
}

int Player::score() {
  int score = 0;
  for (auto it:discard_) {
    score += it->rank().rank() + 1;
  }
  return score;
}

bool Player::isHuman(){}

bool Player::isStartPlayer() {
    // return if player has 7S
    for (int i=0; i<13; i++) {
        if (hand_[i]->suit().suit()==3 && hand_[i]->rank().rank()==6) {
            return true;
        }
    }
    return false;
}

void Player::play(Deck &d) {

}

void Player::play(Deck &d, Card *c) {

}

void Player::discard() {

}

void Player::discard(Card *c) {


}

void Player::addHand(vector<Card*> cards) {
    for (int i=0; i<cards.size(); i++) {
        hand_.push_back(cards[i]);
    }
}


void Player::printHand() {
    std::cout<<"Hand: "<<std::endl;
    for(auto it: hand_) {
      std::cout<<*it<< " ";
    }
    std::cout<<std::endl;
}

vector<Card*> Player::getHand() {
    return hand_;
}
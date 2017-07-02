#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Computer.h"
#include <vector>
using std::vector;

Player::Player(Deck* d, int playerNum): playerNum_(playerNum), deck_(d) {
   updateHand();
//   for (int i=0; i<13; i++) {
//       hand_.push_back(d->getCard(i+playerNum_*13));
//    }
   /*for (auto it:hand_) {
	std::cout<<*it<<std::endl;
   }*/ // prints hand
}

Player::~Player() {
    for (auto it:hand_) {
        delete it;
    }

    for (auto it2:discard_) {
        delete it2;
    }

    hand_.resize(0);
    discard_.resize(0);

    //player responsible for deleting deck?

}


vector<Card*> Player::legalPlay () {
    vector<vector<Card*>> played = deck_->played();
    vector<Card*> legal;
    if (played[3][6] == nullptr) {
        for (auto it:hand_) {
            int suit = it->suit().suit();
            int rank = it->rank().rank();
            if (rank == 6 && suit == 3) {
                legal.push_back(it);
            }
        }
//        Card::Suit suit (3); //SPADE?
//        Card::Rank rank (6); //SEVEN?
//        Card* card = new Card (rank, suit);
//        legal.push_back(card);
//        return legal;
        return legal;
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

void Player::updateScore() {
    score_ += score();
}

int Player::getScore() {
    return score_;
}

bool Player::isHuman(){
    return false;
}

bool Player::isStartPlayer() {
    // return if player has 7S
    for (int i=0; i<13; i++) {
        if (hand_[i]->suit().suit()==3 && hand_[i]->rank().rank()==6) {
            return true;
        }
    }
    return false;
}

void Player::play() {
    std::cout << "player";

}

void Player::play(Card& c) {

}

void Player::discard() {

}

void Player::discard(Card& c) {


}

void Player::updateHand() {
    hand_.clear();
    for (int i=0; i<13; i++) {
        hand_.push_back(deck_->getCard(i+playerNum_*13));
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

vector<Card*> Player::getDiscard() {
    return discard_;
}

int Player::playerNum() {
    return playerNum_;
}

Deck* Player::getDeck() {
    return deck_;
}

void Player::resetDiscard() {
    discard_.clear();
}

Player* Player::rageQuit() {
    std::cout<<"Player "<<playerNum_+1<<" ragequits. A computer will now take over."<<std::endl;
    Player *temp = new Computer(deck_, playerNum_);
    //Player *temp = new Computer(deck_, playerNum_);
    //Computer temp = {deck_, playerNum_};
    //std::swap(temp, *this);
    //std::swap (temp.deck_, deck_);
    //std::swap (temp.discard_, discard_);
    //std::swap (temp.hand_, hand_);
    //std::swap (temp.playerNum_, playerNum_);
    //std::swap (temp.score_, score_);
    //std::swap ((*this), *temp);
    //if ((*temp).isHuman()) std::cout<<"YES"<<std::endl;
    //else std::cout<<"NO"<<std::endl;
    //delete temp;
    return temp;
}

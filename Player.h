#ifndef PLAYER_H
#define PLAYER_H

#include "Card.h"
#include "Deck.h"
#include "Command.h"
#include <vector>
using std::vector;

class Player {
private:
    int playerNum_; //player's number (position in player array)
    Deck* deck_; //game's deck

protected:
    int score_; //player's score
    vector<Card*> hand_; //cards remaining in player's hand
    vector<Card*> discard_; //cards player has discarded

public:
    Player(Deck* d, int playerNum); //Player constructor
    virtual ~Player(); //Player destructor
    Deck* getDeck(); //returns game's deck (deck_)
    int score(); //returns sum of ranks of all discards
    void updateScore(); // returns last stored score + sum of ranks of all discards and updates score_
    int getScore(); //returns player's current score (score_)
    vector<Card*> getHand(); //returns vector of cards remaining in player's hand (hand_)
    vector<Card*> getDiscard(); //returns vector of cards player has discarded
    void resetDiscard(); //removes all cards in player's discard pile 
    virtual bool isHuman(); //returns if player is human
    bool isStartPlayer(); //returns whether player is the start player
    virtual void play(Card& c);
    virtual Card* play(); 
    virtual void discard(Card& c);
    virtual Card* discard();
    void updateHand(); //sets player's hand
    vector<Card*> legalPlay (); //returns legal plays of player based on current hand
    void printHand(); //Prints hand - FOR TEST PURPOSES
    int playerNum(); //returns player's number (position in player array)
    void rageQuit(); //CLI ragequit
    void addScore(int num);
};

#endif //PLAYER_H

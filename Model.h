#ifndef STRAIGHTS_MODEL_H
#define STRAIGHTS_MODEL_H
#include "Subject.h"
#include "Player.h"
#include "Computer.h"
#include "Human.h"
#include <vector>
#include "Deck.h"
using std::vector;

class Model : public Subject {
private:
    vector<Player*> players; //vector of all players in game
    Deck* deck_; //store game's deck
public:
    Model(Deck* d); //Model constructor
    ~Model(); //Model Destructor
    void appendPlayer(Player*); //add player to game
    Player* getPlayers(int pos); //retrieve player by playerNum
    Deck* getDeck(); //return deck
    bool isLegalPlay(int playerNum, Command &command); //returns if command is a legal play
    int startGame(); //starts the game - returns first player's number
    void updatePlayers(int playerNum); //create human and computer players - for start of game and ragequit
    bool isPlay(int playerNum); //returns whether player has any legal plays
    void resetPlayers(); //deletes all players
};

#endif //STRAIGHTS_MODEL_H

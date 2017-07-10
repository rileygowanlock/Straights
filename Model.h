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
    Model(Deck* d);
    ~Model();
    void appendPlayer(Player*); //add player to game
    Player* getPlayers(int pos); //retrieve player by playerNum
    Deck* getDeck(); //return deck
    bool isLegalPlay(Player* player, Command &command); //returns if command is a legal play
    int startGame(); //starts the game - returns first player's number
    void updatePlayers(int playerNum);
};

#endif //STRAIGHTS_MODEL_H

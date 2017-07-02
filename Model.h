#ifndef STRAIGHTS_MODEL_H
#define STRAIGHTS_MODEL_H
#include "Subject.h"
#include "Player.h"
#include <vector>
#include "Deck.h"
#include "Player.h"
using std::vector;

class Model : public Subject {
private:
    vector<Player*> players;
    Deck* deck_;
public:
    Model(Deck* d);
    ~Model();
    void appendPlayer(Player*);
    Player* getPlayers(int pos);
    Deck* getDeck();
    bool isLegalPlay(Player* player, Command &command);
    int startGame();
};

#endif //STRAIGHTS_MODEL_H

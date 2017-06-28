#ifndef STRAIGHTS_MODEL_H
#define STRAIGHTS_MODEL_H
#include <vector>
using std::vector;

class Player;

class Model {
private:
    vector<Player*> players;
public:
    void appendPlayer(Player*);
};

#endif //STRAIGHTS_MODEL_H

#include "Model.h"
#include <vector>
using std::vector;

void Model::appendPlayer(Player* player) {
    players.push_back(player);
};

Player* Model::getPlayers(int pos) {
    return players[pos];
}



#include "Model.h"
#include <vector>
using std::vector;

Model::Model(Deck* d) : deck_(d) {

}

void Model::appendPlayer(Player* player) {
    players.push_back(player);
};

Player* Model::getPlayers(int pos) {
    return players[pos];
}

Deck* Model::getDeck() {
    return deck_;
}

/*bool Model::isLegalPlay(Player* player, Card &card) {
    bool isLegal = false;
    vector<Card*> cards = player->legalPlay();
    for (auto it:cards)  {
        if ((*it)->suit().suit() == c.suit().suit() && (*it)->rank().rank() == c.rank().rank()) {
            return true;
	}
    }
    return isLegal;
}*/

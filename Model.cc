#include "Model.h"
#include <vector>
using std::vector;

Model::Model(Deck* d) : deck_(d) {

}

void Model::appendPlayer(Player* player) {
    players.push_back(player);
}

int Model::startGame() {
    for (int i=0; i<4; i++) {
        if (players[i]->isStartPlayer()) {
            return i;
        }
    }
}

Player* Model::getPlayers(int pos) {
    return players[pos];
}

Deck* Model::getDeck() {
    return deck_;
}

bool Model::isLegalPlay(Player* player, Command &command) {
    bool isLegal = false;
    vector<Card*> cards = player->legalPlay();
    for (auto it:cards)  {
        if ((*it).suit().suit() == command.card.suit().suit() && (*it).rank().rank() == command.card.rank().rank()) {
            isLegal = true;
	    break;
	}
    }
    notify(command.type, player, command.card, isLegal);
    return isLegal;
}

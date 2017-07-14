#include "Model.h"
#include <vector>
using std::vector;

Model::Model(Deck* d) : deck_(d) {

}

Model::~Model() {
//    for (auto it:players) {
//        delete it;
//    }
//
//    //delete deck_;
//    deck_ = nullptr;
//
//    players.resize(0);

}

//add player to game
void Model::appendPlayer(Player* player) {
    players.push_back(player);
}

//start the game - returns first player's number
int Model::startGame() {
    for (int i=0; i<4; i++) {
        if (players[i]->isStartPlayer()) {
            return i;
        }
    }
}

//retrieve player by playerNum
Player* Model::getPlayers(int pos) {
    return players[pos];
}

//return deck
Deck* Model::getDeck() {
    return deck_;
}

//returns if command is a legal play
bool Model::isLegalPlay(int playerNum, Command &command) {
    Player* player = getPlayers(playerNum);
    bool isLegal = false;
    vector<Card*> cards = player->legalPlay();
    vector<Card*> hand = player->getHand();

    //checks if card entered is part of legal plays vector
    if (command.type==Command::Type::PLAY) {
        for (auto it:cards)  {
            if ((*it).suit().suit() == command.card.suit().suit() && (*it).rank().rank() == command.card.rank().rank()) {
                isLegal = true;
                break;
            }
        }
        if (isLegal) {
            if (playerNum == 3) {
                playerNum = 0;
            } else {
            playerNum++;
            }
	}	
    }
    else if (command.type==Command::Type::DISCARD && cards.size()==0) {
        isLegal = true;
    }
    
    if (isLegal) {
        //call notify from subject with state passed in
        //notify(command.type, player, command.card, isLegal);
	    notify(command.type, playerNum, command.card, isLegal);

    } 
    return isLegal;
}

void Model::updatePlayers(int playerNum) {
    if (players[playerNum]->isHuman()) {
        players[playerNum] = new Computer(deck_, playerNum);
    } else {
        players[playerNum] = new Human(deck_, playerNum);
    }
}

bool Model::isPlay(int playerNum) {
    vector<Card*> cards = players[playerNum]->legalPlay();
    if (cards.size()==0) {
        return false;
    }
    return true;
}

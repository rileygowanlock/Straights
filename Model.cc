#include "Model.h"
#include <vector>
using std::vector;

//Model constructor
Model::Model(Deck* d) : deck_(d) { //initialize deck

}

Model::~Model() {

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
	    playerNum++;
            if (playerNum == 4) {
                playerNum = 0;
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

//create human and computer players - for start of game and ragequit
void Model::updatePlayers(int playerNum) {
    if (players[playerNum]->isHuman()) {
        players[playerNum] = new Computer(deck_, playerNum);
    } else {
        players[playerNum] = new Human(deck_, playerNum);
    }
}

//returns whether player has any legal plays
bool Model::isPlay(int playerNum) {
    vector<Card*> cards = players[playerNum]->legalPlay();
    if (cards.size()==0) {
        return false;
    }
    return true;
}

//deletes all players
void Model::resetPlayers() {
    if (players.size()!=0) {
        players.clear();
    }
}

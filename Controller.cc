#include "Controller.h"
#include "View.h"

Controller::Controller(Model* model): model_(model) {}

//choose human or computer player
void Controller::invitePlayers(char playerType, int playerNum) {
    switch(playerType) {
        case 'h': {
            Human* h = new Human(model_->getDeck(), playerNum); //create human
            model_->appendPlayer(h);
            break;
        }
        case 'c': {
            Computer* c = new Computer(model_->getDeck(), playerNum); //create computer
            model_->appendPlayer(c);
            break;
        }
    }
}

//returns first player's number
int Controller::newRound() {
    for (int i = 0; i < 4; i++) {
        model_->getPlayers(i)->updateHand();
        model_->getPlayers(i)->resetDiscard();
    }
    model_->getDeck()->removePlayed();
    int startPlayer = model_->startGame();
    model_->notify(model_->getPlayers(startPlayer));
    return startPlayer;
}

//returns if the card is of type play, discard or bad_command
Command::Type Controller::gamePlay (Card* card, int playerNum) {
    Player* player = model_->getPlayers(playerNum);
    if (model_->isPlay(playerNum)) { //checks if player has a legal play
        Command command(Command::Type::PLAY, *card);
        bool isLegal = model_->isLegalPlay(playerNum, command); //checks if legal card is played
        if (isLegal) {
            player->play(*card); //play card from command
            return command.type;
        }
    } else {
        Command command(Command::Type::DISCARD, *card);
        bool isLegal = model_->isLegalPlay(playerNum, command); //checks if legal card is discarded
        if (isLegal) {
            player->discard(*card); //discard card from command
            //return true;
	    return command.type;
        }
    }
    return Command::Type::BAD_COMMAND;
}

//called if new game
int Controller::newGame(std::vector<std::string> playerType, int seed) {
    model_->getDeck()->createDeck(seed);
   
    model_->getDeck()->shuffle();
    model_->resetPlayers();
    // Invite players
    for (int i = 0; i < 4; i++) {
        if (playerType[i]=="h") {
            invitePlayers('h', i);
        } else {
            invitePlayers('c', i);
        }
    }
    //reset
    for (int i = 0; i < 4; i++) {
        model_->getPlayers(i)->updateHand();
        model_->getPlayers(i)->resetDiscard();
    }
    model_->getDeck()->removePlayed();
    int startPlayer = model_->startGame();
    return startPlayer;
}

//returns position of card for computer to play/discard
int Controller::index(int playerNum) {
    Player *player = model_->getPlayers(playerNum);
    int index = -1;
    vector <Card*> legal = player->legalPlay();
    if (legal.size() != 0) {
        for (int i = 0; i < player->getHand().size(); i++) {
            if (legal[0] == player->getHand()[i]) {
                index = i;
            }
        }
    }
    return index;
}

//play round for computer player
void Controller::playRound(int playerNum) {
    Player *player = model_->getPlayers(playerNum);
    if (!(player->isHuman())) {
        vector <Card*> legal = player->legalPlay();
        if (legal.size() != 0) {
            Card *c = player->play();
            Command command(Command::Type::PLAY, *c);
            card_ = c;
	        playerNum++;
            if (playerNum == 4) {
                playerNum = 0;
            }
            model_->notify(command.type, playerNum, *c, true);
        } else {
            Card *c = player->discard();
            Command command(Command::Type::DISCARD, *c);
            card_ = c;
            model_->notify(command.type, playerNum, *c, true);
        }
    }
}

Card* Controller::getCard() {
    return card_;
}
Player* Controller::getPlayers(int playerNum) {
    return model_->getPlayers(playerNum);
}
void Controller::startNotify(int playerNum) {
    model_->notify(getPlayers(playerNum));
}
void Controller::shuffleDeck() {
    model_->getDeck()->shuffle();
}
void Controller::updatePlayers(int playerNum) {
    model_->updatePlayers(playerNum);
}


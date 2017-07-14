#include "Controller.h"
#include "View.h"
#include "Model.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
#include <string>
#include <iostream>
using std::string;

Controller::Controller(Model* model): model_(model) {}

//directs logic based on human's commands
//bool Controller::gamePlay (Command &command, Player*& player) {
//    if ( command.type == Command::Type::PLAY ) { //play a card
//	bool isLegal = model_->isLegalPlay(player, command); //checls if legal card is played
//	if (isLegal) {
//        player->play(command.card); //play card from command
//	    return true;
//	    }
//    } else if ( command.type == Command::Type::DISCARD ) { //discard a card
//	    bool isLegal = model_->isLegalPlay(player, command); //checks if legal card is discarded
//	    if (isLegal) {
//            player->discard(command.card); //discard card from command
//	        return true;
//        }
//    } else if ( command.type == Command::Type::DECK ) { //print deck
//        model_->getDeck()->print();
//	    return false;
//    } else if ( command.type == Command::Type::QUIT ) { //quit
//	    exit(0);
//    } else if ( command.type == Command::Type::RAGEQUIT ) { //ragequit
//        player->rageQuit(); //changes from human to computer
//        model_->updatePlayers(player->playerNum());
//	    return true;
//    }
//    return false;
//}

//choose human or computer player
void Controller::invitePlayers(char playerType, int playerNum) {

    switch(playerType) {
        case 'h': {
            Human* h = new Human(model_->getDeck(), playerNum);
            model_->appendPlayer(h);
            break;
        }
        case 'c': {
            Computer* c = new Computer(model_->getDeck(), playerNum);
            model_->appendPlayer(c);
            break;
        }
    }
}

//returns first player's number
int Controller::newRound() {
    std::cout<<"Reached New Game"<<std::endl;
    for (int i = 0; i < 4; i++) {
        model_->getPlayers(i)->updateHand();
        model_->getPlayers(i)->resetDiscard();
    }
    model_->getDeck()->removePlayed();
    int startPlayer = model_->startGame();
    model_->notify(model_->getPlayers(startPlayer));
    return startPlayer;
}

Command::Type Controller::gamePlay (Card* card, int playerNum) {
    std::cout<<"Gameplay top: "<<*card<<" and player num: "<<playerNum<<std::endl;
    Player* player = model_->getPlayers(playerNum);
    if (model_->isPlay(playerNum)) { //checks is player has a legal play
        Command command(Command::Type::PLAY, *card);
        bool isLegal = model_->isLegalPlay(playerNum, command); //checks if legal card is played
        if (isLegal) {
	    std::cout<<"Gameplay play: "<<*card<<" and player num: "<<playerNum<<std::endl;
            player->play(*card); //play card from command
            return command.type;
        }
    } else {
        Command command(Command::Type::DISCARD, *card);
        bool isLegal = model_->isLegalPlay(playerNum, command); //checks if legal card is discarded
        if (isLegal) {
            std::cout<<"Gameplay discard: "<<*card<<" and player num: "<<playerNum<<std::endl;
            player->discard(*card); //discard card from command
            //return true;
	    return command.type;
        }
    }
    return Command::Type::BAD_COMMAND;
}

int Controller::newGame(std::vector<std::string> playerType, int seed) { //Note to self: changed this from void to int
    model_->getDeck()->createDeck(seed);
   
    model_->getDeck()->shuffle();
    // Invite players
    for (int i = 0; i < 4; i++) {
        if (playerType[i]=="h") {
            invitePlayers('h', i);
        } else {
            invitePlayers('c', i);
        }
    }
    for (int i = 0; i < 4; i++) {
        model_->getPlayers(i)->updateHand();
        //model_->getPlayers(i)->resetDiscard();
    }
//    //model_->getDeck()->removePlayed();
    int startPlayer = model_->startGame();
    //model_->notify(model_->getPlayers(startPlayer));
    return startPlayer;
}

// just added
int Controller::index(int playerNum) {
    Player *player = model_->getPlayers(playerNum);
    int index = -1;
    if (!(player->isHuman())) {
        //Card *card = player->getHand()[0];
        vector <Card*> legal = player->legalPlay();
        if (legal.size() != 0) {
	    for (int i=0; i<player->getHand().size(); i++) {
		std::cout<<"Leg[0]: "<<*(legal[0])<<* (player->getHand()[i])<<std::endl;
                if (legal[0] == player->getHand()[i]) index=i;
            }
	}
    }

    return index;
}

// just added
void Controller::playRound(int playerNum) {
    //std::cout << "computer or human";
    Player *player = model_->getPlayers(playerNum);
    std::cout<<"PLAYERNUM: "<<playerNum<<std::endl;
    if (!(player->isHuman())) {
	    std::cout << "computer"<<std::endl;
        //Card *card = player->getHand()[0];
        vector <Card*> legal = player->legalPlay();
        if (legal.size() != 0) {
            Card *c = player->play();
            Command command(Command::Type::PLAY, *c);
            card_ = c;
            //std::cout << std::to_string(c->rank().rank());
            //std::cout << std::to_string(c->suit().suit());
	     std::cout <<*c<<std::endl;
	  playerNum++;
          if (playerNum == 4) {
            playerNum = 0;
	    
          }
            model_->notify(command.type, playerNum, *c, true);

        } else {
            Card *c = player->discard();
            Command command(Command::Type::DISCARD, *c);
            card_ = c;
	    //std::cout << std::to_string(c->rank().rank());
            //std::cout << std::to_string(c->suit().suit());
	    std::cout <<*c<<std::endl;
            model_->notify(command.type, playerNum, *c, true);
        }
    }
}

Card* Controller::getCard() {
    return card_;
}



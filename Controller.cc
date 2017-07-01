#include "Controller.h"
#include "View.h"
#include "Model.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
#include <string>
#include <iostream>
using std::string;

Controller::Controller(Model* model): model_(model) {

}

//void Controller::gamePlay (Command::Type &command, Player* player, Card &card) {
bool Controller::gamePlay (Command &command, Player* player) {
    if ( command.type == Command::Type::PLAY ) {
	bool isLegal = model_->isLegalPlay(player, command);
	if (isLegal) {
            player->play(command.card);//play(*(model_->getDeck()), card);
	    return true;
	}
    } else if ( command.type == Command::Type::DISCARD ) {
	bool isLegal = model_->isLegalPlay(player, command);
	if (!isLegal) {
            player->discard(command.card);
	    return true;
        }
    } else if ( command.type == Command::Type::DECK ) {
        model_->getDeck()->print();
	return true;
    } else if ( command.type == Command::Type::QUIT ) {
	//might need to call destructors and delete stuff
	exit(0);
    } else if ( command.type == Command::Type::RAGEQUIT ) { 
	player->rageQuit()
	return true;
    }
    return false;
}

void Controller :: run() {
//    Deck* d = new Deck();
//    d->shuffle(); //I think
//    d->print();
//
//    char playerType;
//    // Invite Players
//    for (int i = 0; i < 4; i++) {
//        view_->invitePlayers(i);
//        std::cin >> playerType;
//        switch(playerType) {
//            case 'h': {
//                Human* h = new Human(*d, i);
//                model_->appendPlayer(h);
//                break;
//	        }
//            case 'c': {
//                Computer* c = new Computer(*d, i);
//                model_->appendPlayer(c);
//                break;
//	        }
//        }
//    }
//
//    // Add hand
//    for (int i = 0; i < 4; i++) {
//        model_->getPlayers(i)->printHand();
//    }


    // continue
//
//    while (true) {
//        string command;
//        string card;
//        std::cin >> command;
//        switch(command) {
//            case "play":
//                cin >> card;
//            case "discard":
//                cin >> card;
//            case "deck":
//            case "quit":
//            case "ragequit":
//        }
//    }
}

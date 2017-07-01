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

void Controller::gamePlay (Command::Type &command, Player* player, Card &card) {
    if ( command == Command::Type::PLAY ) {
	bool isLegal = model_->isLegalPlay(player, card);
	if (isLegal) {
            player->play(card);//play(*(model_->getDeck()), card);
	}
    } else if ( command == Command::Type::DISCARD ) {
	bool isLegal = model_->isLegalPlay(player, card);
	if (!isLegal) {
            player->discard(card);
	}
    } else if ( command == Command::Type::DECK ) {
        model_->getDeck()->print();
    } else if ( command == Command::Type::QUIT ) {

    } else if ( command == Command::Type::RAGEQUIT ) { 
        
    }
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

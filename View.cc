#include "View.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
#include <string>
#include <iostream>

View::View(Model* model, Controller* controller): model_(model), controller_(controller) {}

void View::run() {

    char playerType;
    // Invite Players
    for (int i = 0; i < 4; i++) {
        std::cout << "Is player " << std::to_string(i+1) << " a human(h) or a computer(c)?\n";
        std::cin >> playerType;
        switch(playerType) {
            case 'h': {
                Human* h = new Human(*(model_->getDeck()), i);
                model_->appendPlayer(h);
                break;
            }
            case 'c': {
                Computer* c = new Computer(*(model_->getDeck()), i);
                model_->appendPlayer(c);
                break;
            }
        }
    }
    // testing
    for (int i = 0; i < 4; i++) {
        model_->getPlayers(i)->printHand();
    }
    
    Command command = getCommand();
    controller_->gamePlay (command.type, model_->getPlayers(0), command.card);

    int playerNum = model_->startGame();
    std::cout << "A new round begins. It's player " << std::to_string(playerNum+1) << "'s turn to play.\n";
    Player* player = model_->getPlayers(playerNum);
    if (player->isHuman()) {
        Command command = getCommand();
    } else {
        std::cout << "Is computer" << std::endl;
    }
}

Command View::getCommand() {
    Command command;
    std::cin.ignore();
    std::cin>>command;
    return command;
}

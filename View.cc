#include "View.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
#include <string>
#include <iostream>

View::View(Model* model): model_(model) {}

void View::run() {
    Deck* d = new Deck();
    d->shuffle();
    d->print(); //testing

    char playerType;
    // Invite Players
    for (int i = 0; i < 4; i++) {
        std::cout << "Is player " << std::to_string(i+1) << " a human(h) or a computer(c)?\n";
        std::cin >> playerType;
        switch(playerType) {
            case 'h': {
                Human* h = new Human(*d, i);
                model_->appendPlayer(h);
                break;
            }
            case 'c': {
                Computer* c = new Computer(*d, i);
                model_->appendPlayer(c);
                break;
            }
        }
    }
    // testing
    for (int i = 0; i < 4; i++) {
        model_->getPlayers(i)->printHand();
    }
    std::cout << "A new round begins. It's player " << std::to_string(model_->startGame()) << "'s turn to play.\n";
    Command command = getCommand();
}

Command View::getCommand() {
    Command command;
    std::cin.ignore();
    std::cin>>command;
    return command;
}

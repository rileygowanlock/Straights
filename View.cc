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
                Human* h = new Human(model_->getDeck(), i);
                model_->appendPlayer(h);
                break;
            }
            case 'c': {
                Computer* c = new Computer(model_->getDeck(), i);
                model_->appendPlayer(c);
                break;
            }
        }
    }
    // testing
    for (int i = 0; i < 4; i++) {
        model_->getPlayers(i)->printHand();
    }

    int playerNum = model_->startGame();
    std::cout << "A new round begins. It's player " << std::to_string(playerNum+1) << "'s turn to play.\n";
    Player* player = model_->getPlayers(playerNum);
    if (player->isHuman()) {
        std::string rank[13] = {"Ace","2","3","4","5","6","7","8","9","T","J","Q","K"};
        std::string suitHeader[4] = {"Clubs:","Diamonds:","Hearts:","Spades:"};
        std::cout << "Cards on the table:\n";
        for (int j=0; j<4; j++) {
            std::cout << suitHeader[j];
            for (int i=0; i<13; i++) {
                if (model_->getDeck()->played()[0][i] != nullptr) {
                    std::cout << " " << rank[i];
                }
            }
            std::cout << "\n";
        }
        std::string suit[4] = {"C","D","H","S"};
        std::cout << "Your hand:";
        vector<Card*> hand = player->getHand();
        for (int i=0; i<hand.size(); i++) {
            std::cout << " ";
            std::cout << rank[hand[i]->rank().rank()];
            std::cout << suit[hand[i]->suit().suit()];
        }
        std::cout << "\n";
        std::cout << "Legal plays:";
        vector<Card*> legal = player->legalPlay();
        for (int i=0; i<legal.size(); i++) {
            std::cout << " ";
            std::cout << rank[legal[i]->rank().rank()];
            std::cout << suit[legal[i]->suit().suit()];
        }
        std::cout << "\n";
        Command command = getCommand();
        controller_->gamePlay (command.type, model_->getPlayers(0), command.card);
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

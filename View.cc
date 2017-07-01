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
        std::cout << "Is player " << std::to_string(i+1) << " a human(h) or a computer(c)?\n>";
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

    int startPlayer = model_->startGame();
    int playerNum = startPlayer;
    std::cout << "A new round begins. It's player " << std::to_string(startPlayer+1) << "'s turn to play.\n";
    while (playerNum<4) {
        std::cout << playerNum;

        Player *player = model_->getPlayers(playerNum);
        std::string rank[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
        std::string suitHeader[4] = {"Clubs:", "Diamonds:", "Hearts:", "Spades:"};
        std::string suit[4] = {"C", "D", "H", "S"};
        if (player->isHuman()) {
            std::cout << "Cards on the table:\n";
            for (int j = 0; j < 4; j++) {
                std::cout << suitHeader[j];
                for (int i = 0; i < 13; i++) {
                    if (model_->getDeck()->played()[j][i] != nullptr) {
                        std::cout << " " << rank[i];
                    }
                }
                std::cout << "\n";
            }
            std::cout << "Your hand:";
            vector <Card*> hand = player->getHand();
            for (int i = 0; i < hand.size(); i++) {
                std::cout << " ";
                std::cout << rank[hand[i]->rank().rank()];
                std::cout << suit[hand[i]->suit().suit()];
            }
            std::cout << "\n";
            std::cout << "Legal plays:";
            vector <Card*> legal = player->legalPlay();
            for (int i = 0; i < legal.size(); i++) {
                std::cout << " ";
                std::cout << rank[legal[i]->rank().rank()];
                std::cout << suit[legal[i]->suit().suit()];
            }
            std::cout << "\n";
            Command command = getCommand();
            controller_->gamePlay(command.type, model_->getPlayers(playerNum), command.card);
        } else {
            std::cout << playerNum << "hi";
            vector <Card*> legal = player->legalPlay();
            if (legal.size() != 0) {
                std::cout << "Player " << std::to_string(playerNum+1) << " plays ";
                std::cout << rank[legal[0]->rank().rank()];
                std::cout << suit[legal[0]->suit().suit()] << ".\n";
                player->play();
                // std::cout << "hi";
                // play
            } else {
                std::cout << "Player " << std::to_string(playerNum+1) << " discards ";
                std::cout << rank[legal[0]->rank().rank()];
                std::cout << suit[legal[0]->suit().suit()] << ".\n";
                player->discard();
                // discards
            }
        }

        // End round
//        if (playerNum == startPlayer-1 && player->getHand().size() == 0) {
//            for (int i=0; i<4; i++) {
//                vector<Card*> discard = model_->getPlayers(i)->getDiscard();
//                std::cout << "Player " << std::to_string(i+1) << "'s discards:";
//                for (int i=0; i<discard.size(); i++) {
//                    std::cout << " " << rank[discard[i]->rank().rank()] << suit[discard[i]->suit().suit()];
//                }
//                std::cout << "\n";
//                std::cout << "Player " << std::to_string(i+1) << "'s score:";
//                std::cout << std::to_string(player->getScore()) << "+" << std::to_string(player->score());
//                player->updateScore();
//                std::cout << "=" << std::to_string(player->getScore()) << "\n";
//            }
//            // implement scoring
//            break;
//        }


        if (playerNum == 3) {
            playerNum = 0;
        } else {
            playerNum++;
        }
    }
}

Command View::getCommand() {
    Command command;
    //std::cin.ignore();
    std::cin>>command;
    return command;
}

void View::play (Player *player, Card &card, bool legal) {
    std::cout << "wtf";
    if (!legal) std::cout<<"This is not a legal play.\n";
    else {
        std::cout << "heo";
        std::cout<<"Player "<< std::to_string(player->playerNum()+1) <<" plays "<< card.rank() <<card.suit()<<"hellooooooooo\n";
        std::cout << "helo";
    }
    std::cout << "hellooo";
}

void View::discard (Player *player, Card &card, bool legal) {
    if (legal) std::cout<<"You have a legal play. You may not discard.\n";
    else {
        std::cout<<"Player "<<player->playerNum()+1<<" discards "<<card.rank()<<card.suit()<<"\n";
    }
}

void View::update(Command::Type &command, Player* player, Card &card, bool isLegal) {
    std::cout << "view";
    if ( command == Command::Type::PLAY ) {
        play(player, card, isLegal);
    } else if ( command == Command::Type::DISCARD ) {
        discard(player, card, isLegal);
    }
}

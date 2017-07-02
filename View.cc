#include "View.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
#include <string>
#include <iostream>

View::View(Model* model, Controller* controller): model_(model), controller_(controller) {}

int View::newGame() {
    int startPlayer = controller_->newGame();
    std::cout << "A new round begins. It's player " << std::to_string(startPlayer+1) << "'s turn to play.\n";
    return startPlayer;
}

void View::computer(int playerNum) {
    Player *player = model_->getPlayers(playerNum);
    vector <Card*> legal = player->legalPlay();
    if (legal.size() != 0) {
        std::cout << "Player " << player->playerNum()+1 <<" plays "<< legal[0]->rank() << legal[0]->suit() << "\n";
        player->play();
    } else {
        std::cout << "Player "<< player->playerNum()+1 << " discards " << player->getHand()[0]->rank() << player->getHand()[0]->suit() << "\n";
        player->discard();
    }
}

void View::human(int playerNum) {
    Player *player = model_->getPlayers(playerNum);
    std::string suitHeader[4] = {"Clubs:", "Diamonds:", "Hearts:", "Spades:"};
    std::cout << "Cards on the table:\n";
    for (int j = 0; j < 4; j++) {
        std::cout << suitHeader[j];
        for (int i = 0; i < 13; i++) {
            Card *card = model_->getDeck()->played()[j][i];
            if (card != nullptr) {
                std::cout << " " << card->rank();
            }
        }
        std::cout << "\n";
    }
    std::cout << "Your hand:";
    vector <Card*> hand = player->getHand();
    for (int i = 0; i < hand.size(); i++) {
        std::cout << " ";
        std::cout << hand[i]->rank();
        std::cout << hand[i]->suit();
    }
    std::cout << "\n";
    std::cout << "Legal plays:";
    vector <Card*> legal = player->legalPlay();
    for (int i = 0; i < legal.size(); i++) {
        std::cout << " ";
        std::cout << legal[i]->rank();
        std::cout << legal[i]->suit();
    }
    std::cout << "\n";
    bool legCommand = false;
    while (!legCommand) {
        std::cout << ">";
        Command command = getCommand();
        legCommand = controller_->gamePlay(command, model_->getPlayers(playerNum));
    }

}

void View::playRound(int playerNum, int startPlayer) {
    Player *player = model_->getPlayers(playerNum);
    /*if (player->isHuman()) {
        human(playerNum);
    } else {
        computer(playerNum);
    }*/

    if (player->isHuman()) {
        human(playerNum);
    } if (!(player->isHuman())) {
        computer(playerNum);
    }


//        std::cout << "Cards on the table:\n";
//        for (int j = 0; j < 4; j++) {
//            std::cout << suitHeader[j];
//            for (int i = 0; i < 13; i++) {
//                Card* card = model_->getDeck()->played()[j][i];
//                if (card != nullptr) {
//                    std::cout << " " << card->rank();
//                }
//            }
//            std::cout << "\n";
//        }
//        std::cout << "Your hand:";
//        vector <Card*> hand = player->getHand();
//        for (int i = 0; i < hand.size(); i++) {
//            std::cout << " ";
//            std::cout << hand[i]->rank();
//            std::cout << hand[i]->suit();
//        }
//        std::cout << "\n";
//        std::cout << "Legal plays:";
//        vector <Card*> legal = player->legalPlay();
//        for (int i = 0; i < legal.size(); i++) {
//            std::cout << " ";
//            std::cout << legal[i]->rank();
//            std::cout << legal[i]->suit();
//        }
//        std::cout << "\n";
//        bool legCommand = false;
//        while (!legCommand) {
//            std::cout <<">";
//            Command command = getCommand();
//            legCommand = controller_->gamePlay(command, model_->getPlayers(playerNum));
//        }
//    } else {
//        vector <Card*> legal = player->legalPlay();
//        if (legal.size() != 0) {
//            std::cout << "Player " << player->playerNum()+1 <<" plays "<< legal[0]->rank() << legal[0]->suit() << "\n";
//            player->play();
//        } else {
//            std::cout << "Player "<< player->playerNum()+1 << " discards " << player->getHand()[0]->rank() << player->getHand()[0]->suit() << "\n";
//            player->discard();
//        }
//    }
    if (playerNum == startPlayer-1 && player->getHand().size() == 0) {
        endRound();
    }
}

void View::endRound() {
    bool endGame = false;
    for (int i = 0; i < 4; i++) {
        Player *player = model_->getPlayers(i);
        vector < Card * > discard = player->getDiscard();
        std::cout << "Player " << std::to_string(i + 1) << "'s discards:";
        for (int i = 0; i < discard.size(); i++) {
            std::cout << " " << discard[i]->rank() << discard[i]->suit();
        }
        std::cout << "\n";
        std::cout << "Player " << std::to_string(i + 1) << "'s score:";
        std::cout << " " << std::to_string(player->getScore()) << " + " << std::to_string(player->score());
        player->updateScore();
        std::cout << " = " << std::to_string(player->getScore()) << "\n";
        if (player->getScore() >= 80) {
            endGame = true;
        }
    }

}

void View::run() {
    // Invite Players
    char playerType;
    model_->getDeck()->shuffle();
    for (int i = 0; i < 4; i++) {
        std::cout << "Is player " << std::to_string(i+1) << " a human(h) or a computer(c)?\n>";
        std::cin >> playerType;
        controller_->invitePlayers(playerType, i);
    }
    // Testing
    for (int i = 0; i < 4; i++) {
        model_->getPlayers(i)->printHand();
    }

    int startPlayer = newGame();
    int playerNum = startPlayer;
    while (playerNum<4) {
        playRound(playerNum, startPlayer);
        if (playerNum == 3) {
            playerNum = 0;
        } else {
            playerNum++;
        }
    }



//    int playerNum = startPlayer;
//
//
//
//
//    while (playerNum<4) {
//        Player *player = model_->getPlayers(playerNum);
//        std::string rank[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
//        std::string suitHeader[4] = {"Clubs:", "Diamonds:", "Hearts:", "Spades:"};
//        std::string suit[4] = {"C", "D", "H", "S"};
//        if (player->isHuman()) {
//            std::cout << "Cards on the table:\n";
//            for (int j = 0; j < 4; j++) {
//                std::cout << suitHeader[j];
//                for (int i = 0; i < 13; i++) {
//                    if (model_->getDeck()->played()[j][i] != nullptr) {
//                        std::cout << " " << rank[i];
//                    }
//                }
//                std::cout << "\n";
//            }
//            std::cout << "Your hand:";
//            vector <Card*> hand = player->getHand();
//            for (int i = 0; i < hand.size(); i++) {
//                std::cout << " ";
//                std::cout << rank[hand[i]->rank().rank()];
//                std::cout << suit[hand[i]->suit().suit()];
//            }
//            std::cout << "\n";
//            std::cout << "Legal plays:";
//            vector <Card*> legal = player->legalPlay();
//            for (int i = 0; i < legal.size(); i++) {
//                std::cout << " ";
//                std::cout << rank[legal[i]->rank().rank()];
//                std::cout << suit[legal[i]->suit().suit()];
//            }
//            std::cout << "\n";
//            bool legCommand = false;
//            while (!legCommand) {
//                std::cout <<">";
//                    Command command = getCommand();
//                    legCommand = controller_->gamePlay(command, model_->getPlayers(playerNum));
//            }
//        } else {
//            vector <Card*> legal = player->legalPlay();
//            if (legal.size() != 0) {
//                std::cout<<"Player "<<player->playerNum()+1<<" plays "<<legal[0]->rank()<<legal[0]->suit()<<"\n";
//                player->play();
//            } else {
//                std::cout<<"Player "<<player->playerNum()+1<<" discards "<<player->getHand()[0]->rank()<<player->getHand()[0]->suit()<<"\n";
//                player->discard();
//            }
//        }
//
//        // End round
//        bool endGame;
//        if (playerNum == startPlayer-1 && player->getHand().size() == 0) {
//            for (int i=0; i<4; i++) {
//                Player* player = model_->getPlayers(i);
//                vector<Card*> discard = player->getDiscard();
//                std::cout << "Player " << std::to_string(i+1) << "'s discards:";
//                for (int i=0; i<discard.size(); i++) {
//                    std::cout << " " << rank[discard[i]->rank().rank()] << suit[discard[i]->suit().suit()];
//                }
//                std::cout << "\n";
//                std::cout << "Player " << std::to_string(i+1) << "'s score:";
//                std::cout << " " << std::to_string(player->getScore()) << " + " << std::to_string(player->score());
//                player->updateScore();
//                std::cout << " = " << std::to_string(player->getScore()) << "\n";
//                if (player->getScore() >= 80) {
//                    endGame = true;
//                }
//            }
////            if (endGame) {
////                // repeat
////            }
////            else {
////                // reset
////            }
//        }
//
//        if (playerNum == 3) {
//            playerNum = 0;
//        } else {
//            playerNum++;
//        }
//    }
}

Command View::getCommand() {
    Command command;
    //std::cin.ignore();
    std::cin>>command;
    return command;
}

void View::play (Player *player, Card &card, bool legal) {
    if (!legal) std::cout<<"This is not a legal play.\n";
    else {
        std::cout<<"Player "<< std::to_string(player->playerNum()+1) <<" plays "<< card.rank() <<card.suit()<<"\n";
    }
}

void View::discard (Player *player, Card &card, bool legal) {
    if (legal) std::cout<<"You have a legal play. You may not discard.\n";
    else {
        std::cout<<"Player "<<player->playerNum()+1<<" discards "<<card.rank()<<card.suit()<<"\n";
    }

}

void View::update(Command::Type &command, Player* player, Card &card, bool isLegal) {
    if ( command == Command::Type::PLAY ) {
        play(player, card, isLegal);
    } else if ( command == Command::Type::DISCARD ) {
        discard(player, card, isLegal);
    }
}

//void View::endGame() {
//    run();
//}
//
//void View::newRound() {
//    model_->getDeck()->shuffle();
//}

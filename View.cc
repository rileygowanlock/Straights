#include "View.h"
#include "Deck.h"
#include "Human.h"
#include "Computer.h"
#include <string>
#include <iostream>

View::View(Model* model, Controller* controller): model_(model), controller_(controller) {}

void View::newGame() {
    //startPlayer_ = controller_->newGame();
    std::cout << "A new round begins. It's player " << std::to_string(startPlayer_+1) << "'s turn to play.\n";
}

void View::computer(int playerNum) {
    Player *player = model_->getPlayers(playerNum);
    vector <Card*> legal = player->legalPlay();
    if (legal.size() != 0) {
        std::cout << "Player " << player->playerNum()+1 <<" plays "<< legal[0]->rank() << legal[0]->suit() << ".\n";
        player->play();
    } else {
        std::cout << "Player "<< player->playerNum()+1 << " discards " << player->getHand()[0]->rank() << player->getHand()[0]->suit() << ".\n";
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
        Player* player = model_->getPlayers(playerNum);
        legCommand = controller_->gamePlay(command, player);
    }

}

int View::playRound(int playerNum, int startPlayer) {
    Player *player = model_->getPlayers(playerNum);

    if (player->isHuman()) {
        human(playerNum);
    } if (!(player->isHuman())) {
        computer(playerNum);
    }
    if (startPlayer_==0 && playerNum == 3 && player->getHand().size() == 0) {
        return endRound();
    } else if (playerNum!=3 && playerNum == startPlayer_-1 && player->getHand().size() == 0) {
        return endRound();
    }
    return playerNum;
}

int View::endRound() {
    bool endGame = false;
    int lowScore = 10000;
    vector<int> winners;
    for (int i = 0; i < 4; i++) {
        Player *player = model_->getPlayers(i);
        vector <Card*> discard = player->getDiscard();
        std::cout << "Player " << std::to_string(i + 1) << "'s discards:";
        for (int j = 0; j < discard.size(); j++) {
            std::cout << " " << discard[j]->rank() << discard[j]->suit();
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
    if (endGame) {
        for (int i = 0; i < 4; i++) {
            Player *player = model_->getPlayers(i);
            if (player->getScore() < lowScore) {
                winners.clear();
                winners.push_back(i);
		        lowScore = player->getScore();
            } else if (player->getScore() == lowScore) {
                winners.push_back(i);
            }
        }
        for (int i=0; i<winners.size(); i++) {
            std::cout << "Player " << winners[i]+1 << " wins!\n";
        }
        return 4;
    }
    else {
        model_->getDeck()->shuffle();
        newGame();
        if (startPlayer_ == 0) {
            return 3;
        } else {
            return startPlayer_ - 1;
        }
    }
}

void View::run() {
    // Invite Players
    char playerType;
    model_->getDeck()->shuffle();
    for (int i = 0; i < 4; i++) {
        std::cout << "Is player " << std::to_string(i + 1) << " a human(h) or a computer(c)?\n>";
        std::cin >> playerType;
        controller_->invitePlayers(playerType, i);
    }

    newGame();
    int playerNum = startPlayer_;
    while (playerNum < 4) {
        playerNum = playRound(playerNum, startPlayer_);
        if (playerNum == 3) {
            playerNum = 0;
        } else {
            playerNum++;
        }
    }


}

Command View::getCommand() {
    Command command;
    std::cin>>command;
    return command;
}

void View::play (Player *player, Card &card, bool legal) {
    if (!legal) std::cout<<"This is not a legal play.\n";
    else {
        std::cout<<"Player "<< std::to_string(player->playerNum()+1) <<" plays "<< card.rank() <<card.suit()<<".\n";
    }
}

void View::discard (Player *player, Card &card, bool legal) {
    if (!legal) std::cout<<"You have a legal play. You may not discard.\n";
    else {
        std::cout<<"Player "<<player->playerNum()+1<<" discards "<<card.rank()<<card.suit()<<".\n";
    }

}

void View::update(Player* player) {}

void View::update(Command::Type &command, Player* player, Card &card, bool isLegal) {
//    if ( command == Command::Type::PLAY ) {
//        play(player, card, isLegal);
//    } else if ( command == Command::Type::DISCARD ) {
//        discard(player, card, isLegal);
//    }
}

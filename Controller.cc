#include "Controller.h"
#include "View.h"
#include "Model.h"
#include <string>
#include <iostream>
using std::string;

Controller::Controller(Model* model, View* view) {
    model_ = model;
    view_ = view;
};

void Controller :: run() {
    char playerType;
    // Invite Players
    for (int i = 0; i < 4; i++) {
        view_->invitePlayers(i);
        std::cin >> playerType;
        switch(playerType) {
            case 'h':
                Human* h = new Human;
                model_->players.push_back(h);
            case 'c':
                Computer* c = new Computer;
                model_->players.push_back(c);
        }

    }
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
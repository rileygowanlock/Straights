#include "Controller.h"
#include <string>
#include <iostream>
using std::string;

// this isn't really correct
void Controller :: run() {
    string player;
    // Invite Players
    for (int i = 0; i < 4; i++) {
        std::cout << "Is player " << i << "a human(h) or a computer(c)?\n";
        std::cin >> player;
        // initialize the player class
    }
    // continue

    while (true) {
        string command;
        string card;
        std::cin >> command;
//        switch(command) {
//            case "play":
//                cin >> card;
//            case "discard":
//                cin >> card;
//            case "deck":
//            case "quit":
//            case "ragequit":
//        }
    }
}
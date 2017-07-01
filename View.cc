#include "View.h"
#include <string>
#include <iostream>

void View::invitePlayers(int playerNum) {
    std::cout << "Is player " << std::to_string(playerNum+1) << " a human(h) or a computer(c)?\n";
}

Command View::getCommand() {
    Command command;
    std::cin.ignore();
    std::cin>>command;
    return command;
}

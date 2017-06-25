#include <iostream>
#include "Deck.h"
#include "Card.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Deck* d = new Deck();
    d->shuffle();
    d->print();
    Card* c1 = d->getCard(0);
    Card* c2 = d->getCard(1);
    d->addPlayed(c1);
    d->addPlayed(c2);
    vector<vector<Card*>> list = d->played();
    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++) {
            if (list[i][j] != nullptr) {
                std::cout << *list[i][j] << std::endl;
            }
        }
    }
    return 0;
}
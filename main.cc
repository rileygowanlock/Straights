#include <iostream>
#include "Deck.h"
#include "Card.h"
#include "Human.h"
#include "Computer.h"
#include "Model.h"
#include "View.h"
#include "Deck.h"
#include "Controller.h"
#include "Subject.h"
#include <string>
using std::string;

int main(iny argc, char *argv[]) {
    Deck* d = new Deck();
    //    d->shuffle();
    //    d->print(); //testing
    Model* model = new Model(d);
    Controller* controller = new Controller(model);
    View* view = new View(model, controller);
    model->subscribe(view);
    view->run();


//    delete model;
//    delete view;
//    delete controller;
//    delete d;


// testing
//    std::cout << "Hello, World!" << std::endl;
//    Deck* d = new Deck();
//    d->shuffle();
//    d->print();
//    Card* c1 = d->getCard(0);
//    Card* c2 = d->getCard(1);
//    d->addPlayed(c1);
//    d->addPlayed(c2);
//    vector<vector<Card*>> list = d->played();
//    for (int i=0; i<4; i++) {
//        for (int j=0; j<13; j++) {
//            if (list[i][j] != nullptr) {
//                std::cout << *list[i][j] << std::endl;
//            }
//        }
//    }
//
//    Human* p = new Human(d, 0);
//    Computer* p1 = new Computer(d, 1);
//    Computer* p2 = new Computer(d, 2);
//    Computer* p3 = new Computer(d, 3);
//    vector<Card*> leg = p->legalPlay (list);
//    //When players are created, need to make sure to look for player with 7 of spades and start with him/her
//
//    std::cout<<"Legal plays: "<<std::endl;
//    for (auto it2:leg) {
//	std::cout<<*it2<<std::endl;
//    } // prints legal plays - had to make legalPlay public instead of protected to test/print
//
//    Card* c3 = d->getCard(8);
//    p->play(*c3);
//
//    list = d->played();
//
//    std::cout<<"Played: "<<std::endl;
//    for (int i=0; i<4; i++) {
//        for (int j=0; j<13; j++) {
//            if (list[i][j] != nullptr) {
//                std::cout << *list[i][j] <<" ";
//            }
//        }
//		std::cout <<std::endl;
//    }
//    p->printHand();
//
//    p1->play();
//
//    list = d->played();
//
//    std::cout<<"Played: "<<std::endl;
//    for (int i=0; i<4; i++) {
//        for (int j=0; j<13; j++) {
//            if (list[i][j] != nullptr) {
//                std::cout << *list[i][j] << " ";
//            }
//        }
//	std::cout <<std::endl;
//    }
//     p1->printHand();
//
//     p2->discard();
//     p2->printHand();
//
//    return 0;
}

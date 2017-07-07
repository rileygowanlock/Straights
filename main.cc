#include <iostream>
#include <stdlib.h>
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

int main(int argc, char *argv[]) {
    //std::cout<<argc;
    int seed = 0;
    if (argc>1) {
        seed = atoi(argv[1]);
    }
    Deck* d = new Deck(seed); //create a new Deck
    
//    d->shuffle();
//    d->print(); //testing
    Model* model = new Model(d); // create a Model instance
    Controller* controller = new Controller(model); // create a Controller instance
    View* view = new View(model, controller); // create a View instance
    model->subscribe(view); // add view as an observer of model
    view->run(); // initialize user interface


//    delete model;
//    delete view;
//    delete controller;
//    delete d;


}

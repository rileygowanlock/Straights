#include <iostream>
#include <stdlib.h>
#include "Deck.h"
#include "Card.h"
#include "Human.h"
#include "Computer.h"
#include "Model.h"
#include "View.h"
#include "GUI.h"
#include "Deck.h"
#include "Controller.h"
#include "Subject.h"
#include <gtkmm.h>
#include <string>
using std::string;

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create( argc, argv, "org.Straights" );

    Deck* d = new Deck(0); //create a new Deck
    Model* model = new Model(d); // create a Model instance
    Controller* controller = new Controller(model); // create a Controller instance

    GUI* gui = new GUI(model, controller); // create a View instance
    model->subscribe(gui); // add gui view as an observer of model
    return app->run( *gui );

//    delete model;
//    delete view;
//    delete controller;
//    delete d;

}

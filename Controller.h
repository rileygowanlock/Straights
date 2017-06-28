#ifndef STRAIGHTS_CONTROLLER_H
#define STRAIGHTS_CONTROLLER_H
#include "View.h"
#include "Model.h"

class Controller {
private:
    View* view_;
    Model* model_;
public:
    // queries user input
    // for each command updates model and view with data
    Controller(Model* model, View* view);
    void run();
};

#endif //STRAIGHTS_CONTROLLER_H

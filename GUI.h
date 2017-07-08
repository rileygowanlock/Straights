#ifndef STRAIGHTS_GUI_H
#define STRAIGHTS_GUI_H
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>

class GUI : public Gtk::Window {
public:
    GUI();

protected:
    //Child widgets:
    Gtk::Frame m_Frame;
    Gtk::Box m_Box;
    Gtk::Grid m_Grid;
    Gtk::Image m_Card;
    Gtk::Image* m_Card2;
    std::vector<std::vector<Gtk::Image>> m_Table;
};

#endif //STRAIGHTS_GUI_H
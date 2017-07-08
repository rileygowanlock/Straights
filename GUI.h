#ifndef STRAIGHTS_GUI_H
#define STRAIGHTS_GUI_H
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>

class GUI : public Gtk::Window {
public:
    GUI();
    void new_game();
    void end_game();

protected:
    //Child widgets:
    Gtk::Frame m_Table;
    Gtk::Box m_Window;
    Gtk::Box m_Header;
    Gtk::Grid m_Grid;
    Gtk::Image m_Card;
    Gtk::Button m_Start;
    Gtk::Button m_End;
    Gtk::Entry m_Seed;
};

#endif //STRAIGHTS_GUI_H
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
    Gtk::Frame m_Frame;
    Gtk::Frame m_Frame2;
    Gtk::Box m_Box;
    Gtk::Box m_Box2;
    Gtk::Grid m_Grid;
    Gtk::Image m_Card;
    Gtk::Image* m_Card2;
    Gtk::Button m_Button;
    Gtk::Button m_End;
    Gtk::Entry m_Entry;
    std::vector<std::vector<Gtk::Image>> m_Table;
};

#endif //STRAIGHTS_GUI_H
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

protected:
    //Child widgets:
    Gtk::Frame m_Frame;
    Gtk::Frame m_Frame2;
    Gtk::Box m_Box;
    Gtk::Grid m_Grid;
    Gtk::Image m_Card;
    Gtk::Image* m_Card2;
    Gtk::Button m_Button;
    std::vector<std::vector<Gtk::Image>> m_Table;
};

#endif //STRAIGHTS_GUI_H
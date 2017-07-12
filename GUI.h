#ifndef STRAIGHTS_GUI_H
#define STRAIGHTS_GUI_H
#include "View.h"
#include <gtkmm.h>
#include <iostream>
#include <vector>
#include <string>

class GUI : public View, public Gtk::Window {
private:
    Controller* controller;
    Model* model;
    std::vector<std::string> playerType;
    int startPlayer_;
    int currPlayer_;

public:
    GUI(Model* model, Controller* controller);
    void new_game();
    void end_game();
//    void run() override;
    void setPlayer(int playerNum);
    //void cardPlayed(int i, int j, Player* player, Card* card);
    //void cardPlayed(int i, int j, Card* card);
    void cardPlayed(int index);
    void rage_quit(int i);
    void update(Player* player);
    //void update(Command::Type &command, Player* player, Card &card, bool isLegal);
    void update(Command::Type &command, int playerNum, Card &card, bool isLegal);
    void startDialog(int playerNum);

    void playRound();
    void endRound();
    void human(int playerNum);

protected:
    //Child widgets:
    Gtk::Frame m_Table;
    Gtk::Box m_Window;
    Gtk::Box m_Header;
    Gtk::Grid m_Grid;
    //Gtk::Image m_Card;
    Gtk::Image m_Cards[4][13];
    Gtk::Button m_Start;
    Gtk::Button m_End;
    Gtk::Entry m_Seed;
    
    Gtk::Frame yourHand;
    Gtk::Label title[4];
    Gtk::Frame frame[4];
    Gtk::Button rageQuit[4];
    Gtk::Grid Players;
    Gtk::Box player[4];
    //Gtk::Button button[4];
    Gtk::Grid m_Hand;
    Gtk::Image m_Card;
    Gtk::Button cards[13];
    Gtk::Label points[4];
    Gtk::Label discards[4];

    //Glib::RefPtr<Gio::SimpleActionGroup> m_refActionGroup;
    //Glib::RefPtr<Gio::SimpleAction> m_refAction;
};

#endif //STRAIGHTS_GUI_H

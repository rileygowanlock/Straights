#include "GUI.h"

GUI::GUI() {
    set_title("Straights");
    set_default_size(600, 400);
    set_resizable(false);

    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++) {
            if (i==2 && j==3) {
                std::string imgUrl = "img/"+std::to_string(i)+"_"+std::to_string(j)+".png";
                m_Card = Gtk::Image(imgUrl);
            } else {
                m_Card = Gtk::Image("img/nothing.png");
            }
            m_Grid.attach(m_Card, j, i, 1, 1);
        }
    }
    add(m_Frame);

    m_Grid.set_column_spacing(10);
    m_Grid.set_row_spacing(5);

    m_Frame.add(m_Grid);
    m_Frame.set_label("Cards on the table");

    show_all_children();
}
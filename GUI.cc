#include "GUI.h"

GUI::GUI(): m_Box(Gtk::ORIENTATION_VERTICAL,5), m_Box2(Gtk::ORIENTATION_HORIZONTAL,5) {
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

    m_Button = Gtk::Button("Start new game with seed:");
    m_Button.signal_clicked().connect(sigc::mem_fun(*this, &GUI::new_game));

    m_Entry.set_max_length(10);
    m_Entry.set_text("0");

    m_End = Gtk::Button("End current game");
    m_End.signal_clicked().connect(sigc::mem_fun(*this, &GUI::end_game));

    add(m_Box);
    m_Box2.pack_start(m_Button);
    m_Box2.pack_start(m_Entry);
    m_Box2.pack_start(m_End);
    m_Box.pack_start(m_Box2);
    m_Box.pack_start(m_Frame);

    m_Grid.set_column_spacing(10);
    m_Grid.set_row_spacing(5);

    m_Frame.add(m_Grid);
    m_Frame.set_label("Cards on the table");

    show_all_children();
}
void GUI::new_game() {
    std::cout << "New Game" << std::endl;
}
void GUI::end_game() {
    std::cout << "End Game" << std::endl;
}
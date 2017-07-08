#include "GUI.h"

GUI::GUI(Model* model, Controller* controller): m_Window(Gtk::ORIENTATION_VERTICAL,5),
                                                m_Header(Gtk::ORIENTATION_HORIZONTAL,5),
                                                View(model, controller) {
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

    m_Start = Gtk::Button("Start new game with seed:");
    m_Start.signal_clicked().connect(sigc::mem_fun(*this, &GUI::new_game));

    m_Seed.set_max_length(10);
    m_Seed.set_text("0");

    m_End = Gtk::Button("End current game");
    m_End.signal_clicked().connect(sigc::mem_fun(*this, &GUI::end_game));

    add(m_Window);
    m_Header.pack_start(m_Start);
    m_Header.pack_start(m_Seed);
    m_Header.pack_start(m_End);
    m_Window.pack_start(m_Header);
    m_Window.pack_start(m_Table);

    m_Grid.set_column_spacing(10);
    m_Grid.set_row_spacing(5);

    m_Table.add(m_Grid);
    m_Table.set_label("Cards on the table");

    show_all_children();
}
void GUI::new_game() {
    run();
}
void GUI::end_game() {
    exit(0);
}
#include "GUI.h"

GUI::GUI(Model* model, Controller* controller): m_Window(Gtk::ORIENTATION_VERTICAL,5),
                                                m_Header(Gtk::ORIENTATION_HORIZONTAL,5),
                                                View(model, controller) {
    set_title("Straights");
    set_default_size(500, 400);
    set_resizable(false);

    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++) {
            if (i==2 && j==3) {
                std::string imgUrl = "img/"+std::to_string(i)+"_"+std::to_string(j)+".png";
                m_Cards[i][j] = Gtk::Image(imgUrl);
            } else {
                m_Cards[i][j] = Gtk::Image("img/nothing.png");
            }
            m_Cards[0][0].set_size_request(53);
            m_Grid.attach(m_Cards[i][j], j, i, 1, 1);
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

    m_Grid.set_column_spacing(19);
    m_Grid.set_row_spacing(2);

    m_Table.add(m_Grid);
    m_Table.set_label("Cards on the table");

    for (int i = 0; i < 4; i++) {
        title[i].set_text("Player " + std::to_string(i+1));
        frame[i].set_label_widget(title[i]);//attach(title, i, 0, 1, 1);
        rageQuit[i].set_label("Human");
        player[i] = Gtk::Box(Gtk::ORIENTATION_VERTICAL);
        player[i].pack_start(rageQuit[i]);
        points[i] = Gtk::Label("0 points");
        discards[i] = Gtk::Label("0 discards");
        player[i].pack_start(points[i]);
        player[i].pack_start(discards[i]);
        frame[i].add(player[i]);
        frame[i].set_size_request(211,50);
        Players.attach(frame[i], i, 0, 1, 1);
	//Players.attach(rageQuit[i], i, 0, 1, 1);
	//Players.attach(Player, i, 0, 1, 1);
    }
    Players.set_column_spacing(5);

    m_Window.pack_start(Players);

    int j=0;

    /*for (int i = 0; i < 13; i++) {
        std::string imgUrl = "img/"+std::to_string(0)+"_"+std::to_string(i)+".png";
	m_Card = Gtk::Image(imgUrl);
        cards[i].set_image(m_Card);
        m_Hand.attach((cards[i]), i, 0, 1, 1);
	int position[2] = {i,j};
        cards[i].signal_clicked().connect( sigc::bind<int, int>(sigc::mem_fun(*this,&GUI::cardPlayed),i,j));
    }*/
    yourHand.set_label("Your hand");
    //m_Hand.attach(yourHand, 0, 0, 1, 1);
    for (int i = 0; i < 13; i++) {
        std::string imgUrl = "img/nothing.png";
	    m_Card = Gtk::Image(imgUrl);
        cards[i].set_image(m_Card);
        m_Hand.attach((cards[i]), i+1, 0, 1, 1);
    }
    yourHand.add(m_Hand);

    m_Window.pack_start(yourHand);


    show_all_children();
}
void GUI::new_game() {
    run();
}
void GUI::end_game() {
    exit(0);
}

void GUI::run() {
    model_->getDeck()->shuffle();
    for (int i = 0; i < 4; i++) {
        controller_->invitePlayers('h', i);
    }
    Player *player = model_->getPlayers(0);
    vector <Card*> hand = player->getHand();
    for (int i = 0; i < hand.size(); i++) {
        std::string imgUrl = "img/"+std::to_string(hand[i]->suit().suit())+"_"+std::to_string(hand[i]->rank().rank())+".png";
	m_Card = Gtk::Image(imgUrl);
        cards[i].set_image(m_Card);
        cards[i].signal_clicked().connect( sigc::bind<int, int>(sigc::mem_fun(*this,&GUI::cardPlayed),hand[i]->rank().rank(),hand[i]->suit().suit()));
    }
}

void GUI::cardPlayed(int i, int j) {
    std::string imgUrl = "img/"+std::to_string(j)+"_"+std::to_string(i)+".png";
    m_Cards[j][i].set(imgUrl);
    show_all_children();
}

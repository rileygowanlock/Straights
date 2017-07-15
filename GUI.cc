#include "GUI.h"

GUI::GUI(Model* model, Controller* controller): m_Window(Gtk::ORIENTATION_VERTICAL),
                                                m_Header(Gtk::ORIENTATION_HORIZONTAL),
                                                View(model, controller) {
    set_title("Straights");
    set_default_size(500, 400);
    set_resizable(false);

    playerType = {"h","h","h","h"}; //tracks whether the player is a human or computer

    //specifies when the game starts and resets
    start_ = true;
    reset_ = false;

    //populate table with blank cards in a grid 4*13
    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++) {
            m_Cards[i][j] = Gtk::Image("img/nothing.png");
            m_Cards[0][0].set_size_request(53); //
            m_Grid.attach(m_Cards[i][j], j, i, 1, 1);
        }
    }

    //enables Start button
    m_Start = Gtk::Button("Start new game with seed:");
    m_Start.signal_clicked().connect(sigc::mem_fun(*this, &GUI::new_game));
    m_Seed.set_max_length(10); //specifies max number of digits
    m_Seed.set_text("0"); //default value

    //enables End button
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
        frame[i].set_label_widget(title[i]);
        rageQuit[i].set_label("Human");
        rageQuit[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &GUI::rage_quit),i));
        player[i] = Gtk::Box(Gtk::ORIENTATION_VERTICAL);
        player[i].pack_start(rageQuit[i]);
        points[i] = Gtk::Label("0 points");
        discards[i] = Gtk::Label("0 discards");
        player[i].pack_start(points[i]);
        player[i].pack_start(discards[i]);
        frame[i].add(player[i]);
        frame[i].set_size_request(211,50);
        Players.attach(frame[i], i, 0, 1, 1);
    }
    Players.set_column_spacing(5);
    m_Window.pack_start(Players);

    yourHand.set_label("Your hand");
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
    // Change buttons to Rage!
    for (int i=0; i<4; i++) {
        rageQuit[i].set_label("Rage!");
        discards[i].set_label("0 discards");
        for (int j=0; j<13; j++) {
            std::string imgUrl = "img/nothing.png";
            m_Cards[i][j].set(imgUrl);
        }
    }
    startPlayer_ = controller_->newGame(playerType,std::stoi(m_Seed.get_text())); // Start game
    currPlayer_ = startPlayer_;
    controller_->startNotify(startPlayer_);

    Player* player = controller_->getPlayers(startPlayer_);
    computer(player);
}

void GUI::playRound() {
    Player* player = controller_->getPlayers(currPlayer_);
    if (startPlayer_ == currPlayer_ && player->getHand().size() == 0) {
        endRound();
    }
}

void GUI::endRound() {
    bool endGame = false;
    int lowScore = 10000;
    int score = 0;
    vector<int> winners;
    string text = "";
    string suits = "CDHS";
    string ranks = "A23456789TJQK";
    for (int i = 0; i < 4; i++) {
        Player* player = controller_->getPlayers(i);
        vector <Card*> discard = player->getDiscard();
        text += "Player " + std::to_string(i + 1) + "'s discards:";
        for (int j = 0; j < discard.size(); j++) {
            text += " ";
            text+=ranks[discard[j]->rank().rank()];
            text+=suits[discard[j]->suit().suit()];
	    }
        text +=  "\n";
        text +=  "Player " + std::to_string(i + 1) + "'s score:";
	    score = player->score();
        text +=  " " + std::to_string(player->getScore()) + " + " + std::to_string(score);
        player->updateScore();
        text += " = " + std::to_string(player->getScore()) + "\n";
        if (player->getScore() >= 80) {
            endGame = true;
        }
    }
    Gtk::MessageDialog dialog(*this, text);
    dialog.run();
    if (endGame) {
        for (int i = 0; i < 4; i++) {
            Player* player = controller_->getPlayers(i);
            //Player *player = model_->getPlayers(i);
            if (player->getScore() < lowScore) {
                winners.clear();
                winners.push_back(i);
                lowScore = player->getScore();
            } else if (player->getScore() == lowScore) {
                winners.push_back(i);
            }
        }
        for (int i = 0; i < winners.size(); i++) {
            text = "Player " + std::to_string(winners[i] + 1) + " wins!";
            Gtk::MessageDialog dialog(*this, text);
            dialog.run();
        }
        resetScreen();
    } else {
        resetScreen();
        for (int i=0; i<4; i++) {
            rageQuit[i].set_label("Rage!");
        }
        controller_->shuffleDeck();
        currPlayer_ = controller_->newRound();
        startPlayer_ = currPlayer_;
        Player* player = controller_->getPlayers(startPlayer_);
        computer(player);
    }
    show_all_children();
}

void GUI::resetScreen() {
    reset_ = true;
    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++) {
            m_Cards[i][j].set("img/nothing.png");
        }
    }
    for (int i = 0; i < 4; i++) {
        points[i].set_label("0 points");
        discards[i].set_label("0 discards");
    }
    for (int i=0; i<4; i++) {
        rageQuit[i].set_sensitive(true);
        if (playerType[i] == "h") {
            rageQuit[i].set_label("Human");
        } else if (playerType[i] == "c") {
            rageQuit[i].set_label("Computer");
        }
    }
    //show_all_children();
}

void GUI::end_game() {
    exit(0);
}

void GUI::rage_quit(int i) {
    std::string label = rageQuit[i].get_label();
    if (label=="Computer") {
        rageQuit[i].set_label("Human");
        playerType[i] = "h";
    } else if (label=="Human") {
        rageQuit[i].set_label("Computer");
        playerType[i] = "c";
    } else if (label=="Rage!" && rageQuit[i].get_sensitive()) {
        rageQuit[i].set_sensitive(false);
        controller_->updatePlayers(i);
        playerType[i] = "c";
        Player* player = controller_->getPlayers(startPlayer_);
        computer(player);
    }
}

void GUI::cardPlayed(int index) {
    Player* player = controller_->getPlayers(currPlayer_);
    if (index>=player->getHand().size()) return;
    Card* card = player->getHand()[index];
    int i = card->rank().rank();
    int j = card->suit().suit();
    Command::Type validPlay = controller_->gamePlay(card, currPlayer_);
    if (validPlay != Command::Type::BAD_COMMAND) {
        currPlayer_++;
        if (currPlayer_ == 4) {
            currPlayer_ = 0;
        }
    }
    // copy card to table
    if (validPlay == Command::Type::PLAY) {
        std::string imgUrl = "img/"+std::to_string(j)+"_"+std::to_string(i)+".png";
        m_Cards[j][i].set(imgUrl);
        show_all_children();
    }
    playRound();
    player = controller_->getPlayers(currPlayer_);
	computer(player);
}

void GUI::computer(Player* player) {
    int index = -1;
	while (playerType[currPlayer_]=="c") {
        if (reset_) {
            reset_ = false;
            break;
        }
        index = controller_->index(currPlayer_);
        if (index != -1) {
            Player* player = controller_->getPlayers(currPlayer_);
            Card* card = player->getHand()[index];
            int i = card->rank().rank();
            int j = card->suit().suit();
            std::string imgUrl = "img/"+std::to_string(j)+"_"+std::to_string(i)+".png";
            m_Cards[j][i].set(imgUrl);
            show_all_children();
        }
        playRound(); // check if round is done
        controller_->playRound(currPlayer_);
	    if (index != -1) {
        currPlayer_++;
            if (currPlayer_ == 4) {
                currPlayer_ = 0;
            }
        }
        playRound();
    }
}

void GUI::setPlayer(int playerNum) {
    for (int i=0; i<4; i++) {
        if (playerType[i]=="c") {
            rageQuit[i].set_sensitive(false);
        } else {
            if (i!=playerNum) {
                rageQuit[i].set_sensitive(false);
            } else {
                rageQuit[i].set_sensitive(true);
            }
        }
    }
}

void GUI::startDialog(int playerNum) {
    string text = "A new round begins. It's player " + std::to_string(playerNum+1) + "\'s turn to play.";
    Gtk::MessageDialog dialog(*this, text);
    dialog.run();
}

void GUI::update(Player* player) {
    startDialog(player->playerNum());
    vector<Card*> hand = player->getHand();
    setPlayer(player->playerNum());
    for (int i = 0; i < hand.size(); i++) {
        std::string imgUrl = "img/" + std::to_string(hand[i]->suit().suit()) + "_" + std::to_string(hand[i]->rank().rank()) + ".png";
        m_Card = Gtk::Image(imgUrl);
        cards[i].set_image(m_Card);
        if (start_) {
            cards[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &GUI::cardPlayed), i));
        }
    }
    start_ = false;
    show_all_children();
}

void GUI::update(Command::Type &command, int playerNum, Card &card, bool isLegal) {
    Player* player = controller_->getPlayers(playerNum);
    vector <Card*> discardPile = (player->getDiscard());
    if (command == Command::Type::DISCARD && isLegal) {
        if (player->isHuman()) {
            discards[playerNum].set_label(std::to_string(player->getDiscard().size()+1) + " discards");
        } else {
            discards[playerNum].set_label(std::to_string(player->getDiscard().size()) + " discards");
            currPlayer_++;
            if (currPlayer_ == 4) {
                 currPlayer_ = 0;
            }
        }
        playerNum++;
        if (playerNum == 4) {
            playerNum = 0;
        }
    }
    player = controller_->getPlayers(playerNum);
    vector<Card*> hand = player->getHand();
    setPlayer(playerNum);
    for (int i = 0; i < 13; i++) {
        if (i<hand.size()) {
            std::string imgUrl = "img/"+std::to_string(hand[i]->suit().suit())+"_"+std::to_string(hand[i]->rank().rank())+".png";
            m_Card = Gtk::Image(imgUrl);
            cards[i].set_image(m_Card);
        } else {
            std::string imgUrl = "img/nothing.png";
            m_Card = Gtk::Image(imgUrl);
            cards[i].set_image(m_Card);
        }
    }
    show_all_children();
}


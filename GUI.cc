#include "GUI.h"

GUI::GUI(Model* model, Controller* controller): m_Window(Gtk::ORIENTATION_VERTICAL,5),
                                                m_Header(Gtk::ORIENTATION_HORIZONTAL,5),
                                                View(model, controller) {
    set_title("Straights");
    set_default_size(500, 400);
    set_resizable(false);
    playerType = {"h","h","h","h"};
    start_ = true;

    for (int i=0; i<4; i++) {
        for (int j=0; j<13; j++) {
            m_Cards[i][j] = Gtk::Image("img/nothing.png");
            m_Cards[0][0].set_size_request(53); //formatting
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
    // Change buttons to Rage!
    for (int i=0; i<4; i++) {
        rageQuit[i].set_label("Rage!");
    }
    m_Start.set_sensitive(false); // Need to change this
    startPlayer_ = controller_->newGame(playerType,std::stoi(m_Seed.get_text())); // Start game
    currPlayer_ = startPlayer_;
    model_->notify(model_->getPlayers(startPlayer_)); // change this

    std::cout<<"HERE"<<std::endl;

    /*int playerNum = startPlayer_;
    std::cout<<playerNum<<std::endl;
    while (playerNum < 4) {
    std::cout<<playerNum<<std::endl;
        playerNum = playRound(playerNum, startPlayer_);
        if (playerNum == 3) {
            playerNum = 0;
        } else {
            playerNum++;
        }
    }*/

}

void GUI::playRound() {
    controller_->playRound(currPlayer_);
//    Player *player = model_->getPlayers(currPlayer_);
//    if (!(player->isHuman())) {
//        std::cout << "computer";
//        vector <Card*> legal = player->legalPlay();
//        if (legal.size() != 0) {
//            std::cout << "Player " << player->playerNum()+1 <<" plays "<< legal[0]->rank() << legal[0]->suit() << ".\n";
//            // should call controller
//            player->play();
//        } else {
//            std::cout << "Player "<< player->playerNum()+1 << " discards " << player->getHand()[0]->rank() << player->getHand()[0]->suit() << ".\n";
//            // should call controller
//            player->discard();
//        }
//	if (legal.size() != 0) {
//            player->play();
//        } else {
//            player->discard();
//        }
        /*if (currPlayer_ == 3) {
            currPlayer_ = 0;
        } else {
            currPlayer_++;
        }*/
    }
//    std::cout<<"playRound"<<std::endl;
//    if (startPlayer_==0 && currPlayer_ == 3 && player->getHand().size() == 1) {
//        endRound();
//    } else if (currPlayer_!=3 && currPlayer_ == startPlayer_-1 && player->getHand().size() == 1) {
//        endRound();
//    }
//}

void GUI::endRound() {
    bool endGame = false;
    int lowScore = 10000;
    vector<int> winners;
    string text = "";
    for (int i = 0; i < 4; i++) {
        Player *player = model_->getPlayers(i);
        vector < Card * > discard = player->getDiscard();
        text += "Player " + std::to_string(i + 1) + "'s discards:";
        /*for (int j = 0; j < discard.size(); j++) {
            text +=  " ";
	    text<<discard[j];
        }*/
        text += "\n";
        text += "Player " + std::to_string(i + 1) + "'s score:";
        text += " " + std::to_string(player->getScore()) + " + " + std::to_string(player->score());
        player->updateScore();
        text += " = " + std::to_string(player->getScore()) + "\n";
        if (player->getScore() >= 80) {
            endGame = true;
        }
    }
    Gtk::MessageDialog dialog(*this, text);
    dialog.run();
    /*if (endGame) {
        for (int i = 0; i < 4; i++) {
            Player *player = model_->getPlayers(i);
            if (player->getScore() < lowScore) {
                winners.clear();
                winners.push_back(i);
		        lowScore = player->getScore();
            } else if (player->getScore() == lowScore) {
                winners.push_back(i);
            }
        }
        for (int i=0; i<winners.size(); i++) {
            std::cout << "Player " << winners[i]+1 << " wins!\n";
        }
      //  return 4;
    }
    else {
        model_->getDeck()->shuffle();
        newGame();
        if (startPlayer_ == 0) {
           // return 3;
        } else {
           // return startPlayer_ - 1;
        }
    }*/
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
        model_->updatePlayers(i); // move to controller?
    }
    //playRound();
}

//void GUI::run() {
//    model_->getDeck()->createDeck(std::stoi(m_Seed.get_text()));
//    model_->getDeck()->shuffle();
//    for (int i = 0; i < 4; i++) {
//        if (rageQuit[i].get_label()=="Human") {
//            controller_->invitePlayers('h', i);
//        } else if (rageQuit[i].get_label()=="Computer") {
//            controller_->invitePlayers('c', i);
//        }
//    }
//    Player *player = model_->getPlayers(0);
//    vector <Card*> hand = player->getHand();
//    for (int i = 0; i < hand.size(); i++) {
//        std::string imgUrl = "img/"+std::to_string(hand[i]->suit().suit())+"_"+std::to_string(hand[i]->rank().rank())+".png";
//	    m_Card = Gtk::Image(imgUrl);
//        cards[i].set_image(m_Card);
//        cards[i].signal_clicked().connect(sigc::bind<int, int>(sigc::mem_fun(*this,&GUI::cardPlayed),hand[i]->rank().rank(),hand[i]->suit().suit()));
//    }
//    for (int i=0; i<4; i++) {
//        rageQuit[i].set_label("Rage!");
//    }
//}

void GUI::cardPlayed(int index) {
    Card* card = model_->getPlayers(currPlayer_)->getHand()[index];
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
}

void GUI::computer() {
    int i = controller_->getCard()->rank().rank();
    int j = controller_->getCard()->suit().suit();
    std::cout << i;
    std::cout << j;
    std::string imgUrl = "img/"+std::to_string(j)+"_"+std::to_string(i)+".png";
    m_Cards[j][i].set(imgUrl);
    currPlayer_++;
    if (currPlayer_ == 4) {
        currPlayer_ = 0;
    }
    show_all_children();
}

void GUI::setPlayer(int playerNum) {
    std::cout << "setPlayer";
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
    //dialog.set_secondary_text("And this is the secondary text that explains things.");
    dialog.run();
    show_all_children();
}

void GUI::update(Player* player) {
    startDialog(player->playerNum());
    vector<Card*> hand = player->getHand();
    setPlayer(player->playerNum());
    if (playerType[player->playerNum()]=="c") {
        controller_->playRound(currPlayer_);
    } else {
        // Show hand
        for (int i = 0; i < hand.size(); i++) {
            std::string imgUrl = "img/" + std::to_string(hand[i]->suit().suit()) + "_" + std::to_string(hand[i]->rank().rank()) + ".png";
            m_Card = Gtk::Image(imgUrl);
            cards[i].set_image(m_Card);
            //cards[i].signal_clicked().connect(sigc::bind<int, int, Player*, Card*>(sigc::mem_fun(*this,&GUI::cardPlayed),hand[i]->rank().rank(),hand[i]->suit().suit(),player,hand[i]));
            //cards[i].signal_clicked().connect(sigc::bind<int, int, Card*>(sigc::mem_fun(*this,&GUI::cardPlayed),hand[i]->rank().rank(),hand[i]->suit().suit(),hand[i]));
            cards[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &GUI::cardPlayed), i));
        }
    }
}

void GUI::update(Command::Type &command, int playerNum, Card &card, bool isLegal) {
    std::cout << std::to_string(currPlayer_);
    std::cout << std::to_string(playerNum);
    std::cout << "running";
    if (playerType[playerNum]=="c" && command==Command::Type::PLAY) {
        std::cout << "hi";
        computer();
        playerNum++;
        if (playerNum == 4) {
            playerNum = 0;
        }
    }
    Player* player = model_->getPlayers(playerNum);
    if (command == Command::Type::DISCARD && isLegal) {
        discards[playerNum].set_label(std::to_string(player->getDiscard().size()+1) + " discards");
        playerNum = currPlayer_;
    }
    player = model_->getPlayers(playerNum);
    vector<Card*> hand = player->getHand();
    setPlayer(playerNum);
    // should this only happen if not computer?
    std::cout<<"Reached update func. Player num: "<<player->playerNum()<<std::endl;
    for (int i = 0; i < 13; i++) {
        if (i<hand.size()) {
            std::string imgUrl = "img/"+std::to_string(hand[i]->suit().suit())+"_"+std::to_string(hand[i]->rank().rank())+".png";
            m_Card = Gtk::Image(imgUrl);
            cards[i].set_image(m_Card);
            //cards[i].signal_clicked().connect(sigc::bind<int>(sigc::mem_fun(*this, &GUI::cardPlayed), i));
            //cards[i].signal_clicked().connect(sigc::bind<int, int, Card*>(sigc::mem_fun(*this,&GUI::cardPlayed), hand[i]->rank().rank(),hand[i]->suit().suit(),hand[i]));
        }
        else {
            std::string imgUrl = "img/nothing.png";
            m_Card = Gtk::Image(imgUrl);
            cards[i].set_image(m_Card);
        }
    }
    show_all_children();
//    if (playerType[playerNum]=="c") {
//        controller_->playRound(playerNum);
//    }
}

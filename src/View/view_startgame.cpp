#include "View/view_startgame.h"

View_StartGame::View_StartGame(View_Main &main_ui) {
	window = main_ui.getWindow();
	wp = NULL;
	bp = NULL;
}
void View_StartGame::startGame() {
	greeting->hide();
	
	// set white player type
	QList<QRadioButton*> wLst = greeting->findChild<QGroupBox*>("White player")->findChildren<QRadioButton*>();
	if (wLst.at(0)->isChecked()) wPlr = HUMAN;
	else if (wLst.at(1)->isChecked()) wPlr = AI;
	else if (wLst.at(2)->isChecked()) wPlr = NETWORK;
	
	// set black player type
	QList<QRadioButton*> bLst = greeting->findChild<QGroupBox*>("Black player")->findChildren<QRadioButton*>();
	if (bLst.at(0)->isChecked()) bPlr = HUMAN;
	else if (bLst.at(1)->isChecked()) bPlr = AI;
	else if (bLst.at(2)->isChecked()) bPlr = NETWORK;
	
	// set up players
	setupPlayerBegin(WHITE);
}
View_StartGame::~View_StartGame() {
	qDebug()<<"wp dell";
	if (wp) delete wp;
	qDebug()<<"bp dell";
	if (bp) delete bp;
}
void View_StartGame::setupPlayerBegin(COLOR color) {
	curColor = color;
	PLAYER_TYPE plr = (color == WHITE ? wPlr : bPlr);
	
	// settings box
	QFrame *settings = new QFrame(window);
	settingsBox = settings;
	settings->setGeometry(40, 40, 720, 340);
	settings->setFrameStyle(QFrame::Box | QFrame::Plain);
	settings->setLineWidth(3);
	settings->show();
	
	// header text
	QLabel *header = new QLabel(color == WHITE ? "White player settings" : "Black player settings", settings);
	header->setGeometry(10, 5, 700, 30);
	header->show();
	
	// next button
	QPushButton *_next_btn = new QPushButton("Next >>", settings);
	next_btn = _next_btn;
	_next_btn->setGeometry(260, 280, 200, 45);
	_next_btn->show();
	
	connect(this, SIGNAL(setupPlayerEndSignal(Player*)), SLOT(setupPlayerEndSlot(Player*)));
	
	// players' settings
	if (plr == HUMAN) {
		emit setupPlayerEndSignal(NULL);
	} else if (plr == AI) {
		AiPlr = new Ai_Player();
		AiPlr->setColor(color);
		setupAi();
	} else if (plr == NETWORK) {
		NetworkPlr = new Network_Player();
		NetworkPlr->setColor(color);
		setupNetwork();
	} else {
		exit(1);
	}
}
// set up ai
void View_StartGame::setupAi() {
	// begin
	setupAiShowLevel();
}
void View_StartGame::setupAiEnd() {
	Player *p = (Player*)AiPlr;
	emit setupPlayerEndSignal(p);
}
// ai level
void View_StartGame::setupAiShowLevel() {
	QGroupBox *ai_level = new QGroupBox(settingsBox);
	ai_level->setObjectName("Ai level");
	ai_level->setGeometry(180, 40, 360, 240);
	QLabel *ai_level_Label = new QLabel("Ai Level:");
	QRadioButton *ai_level_1 = new QRadioButton("Easy");
	QRadioButton *ai_level_2 = new QRadioButton("Medium");
	QRadioButton *ai_level_3 = new QRadioButton("Hard");
	ai_level_2->setChecked(true);
	QVBoxLayout *ai_level_Layout = new QVBoxLayout;
	ai_level_Layout->addWidget(ai_level_Label);
	ai_level_Layout->addWidget(ai_level_1);
	ai_level_Layout->addWidget(ai_level_2);
	ai_level_Layout->addWidget(ai_level_3);
	ai_level->setLayout(ai_level_Layout);
	ai_level->show();
	connect(next_btn, SIGNAL(clicked()), SLOT(setupAiGetLevel()));
}
void View_StartGame::setupAiGetLevel() {
	disconnect(next_btn, SIGNAL(clicked()), this, SLOT(setupAiGetLevel()));
	settingsBox->findChild<QGroupBox*>("Ai level")->hide();
	QList<QRadioButton*> ai_level = settingsBox->findChild<QGroupBox*>("Ai level")->findChildren<QRadioButton*>();
	if (ai_level.at(0)->isChecked()) AiPlr->setLevel(2);
	else if (ai_level.at(1)->isChecked()) AiPlr->setLevel(4);
	else if (ai_level.at(2)->isChecked()) AiPlr->setLevel(6);
	// end
	setupAiEnd();
}

// set up network
void View_StartGame::setupNetwork() {
	// begin
	setupNetworkShowInterface();
}
void View_StartGame::setupNetworkEnd() {
	Player *p = (Player*)NetworkPlr;
	emit setupPlayerEndSignal(p);
}
// network interface
void View_StartGame::setupNetworkShowInterface() {
	QList<QString> listIP = NetworkPlr->getSelfIpAddresses();
	QLabel *listip_box_label = new QLabel("Network Interface:", settingsBox);
	listip_box_label->setObjectName("Network Interface Label");
	listip_box_label->setGeometry(180, 80, 360, 30);
	listip_box_label->show();
	QComboBox *listip_box = new QComboBox(settingsBox);
	listip_box->setObjectName("Network Interface");
	listip_box->setGeometry(180, 120, 360, 60);
	foreach (QString ip, listIP) {
		listip_box->addItem(ip);
	}
	listip_box->show();
	connect(next_btn, SIGNAL(clicked()), SLOT(setupNetworkGetInterface()));
}
void View_StartGame::setupNetworkGetInterface() {
	disconnect(next_btn, SIGNAL(clicked()), this, SLOT(setupNetworkGetInterface()));
	settingsBox->findChild<QLabel*>("Network Interface Label")->hide();
	settingsBox->findChild<QComboBox*>("Network Interface")->hide();
	QString choosedIP = settingsBox->findChild<QComboBox*>("Network Interface")->currentText();
	NetworkPlr->setSelfIp(choosedIP);
	NetworkPlr->createServer();
	// next
	setupNetworkShowSearch();
}
// network search
void View_StartGame::setupNetworkShowSearch() {
	NetworkPlr->sendAnnouncement();
	QLabel *listip_box_label = new QLabel("Search enemies:", settingsBox);
	listip_box_label->setObjectName("Network Search Label");
	listip_box_label->setGeometry(180, 80, 360, 30);
	listip_box_label->show();
	QComboBox *listip_box = new QComboBox(settingsBox);
	listip_box->setObjectName("Network Search");
	listip_box->setGeometry(180, 120, 360, 60);
	listip_box->show();
	QLineEdit* textIP = new QLineEdit(settingsBox);
	textIP->setObjectName("Network IP");
	textIP->setGeometry(180, 200, 360, 60);
	textIP->show();
	QLabel *ERROR_box_label = new QLabel("", settingsBox);
	ERROR_box_label->setObjectName("ERROR_IP");
	ERROR_box_label->setGeometry(180, 40, 360, 30);
	ERROR_box_label->show();
	connect(NetworkPlr, SIGNAL(searchUpdate()), SLOT(setupNetworkUpdateSearch1()));
	connect(NetworkPlr, SIGNAL(connectComplete()), SLOT(setupNetworkUpdateSearch2()));
	connect(next_btn, SIGNAL(clicked()), SLOT(setupNetworkIP()));
	connect(textIP, SIGNAL(returnPressed()), SLOT(setupNetworkIP()));
}

void View_StartGame::setupNetworkIP(){
	QString IP=settingsBox->findChild<QLineEdit*>("Network IP")->text();
	if(NetworkPlr->isIp(IP)==1){
		if (IP == "") {
			setupNetworkGetSearch();
			return;
		}
		qDebug()<<"is not ip"<<IP;
		QString err="IS NOT IP:";		
		settingsBox->findChild<QLabel*>("ERROR_IP")->setText(err+IP);
		return;
	}
	disconnect(next_btn, SIGNAL(clicked()), this, SLOT(setupNetworkGetSearch()));
	QString choosedIP = settingsBox->findChild<QComboBox*>("Network Search")->currentText();
	NetworkPlr->createClient(IP);
}
void View_StartGame::setupNetworkUpdateSearch1() {
	QList<QString> listIP = NetworkPlr->getEnemyIpAddresses();
	settingsBox->findChild<QComboBox*>("Network Search")->clear();
	foreach (QString ip, listIP) {
		settingsBox->findChild<QComboBox*>("Network Search")->addItem(ip);
	}
}
void View_StartGame::setupNetworkUpdateSearch2() {
	// end
	qDebug() << "update search 2";
	setupNetworkEnd();
}
void View_StartGame::setupNetworkGetSearch() {
	if (!settingsBox->findChild<QComboBox*>("Network Search")->count()) return;
	disconnect(NetworkPlr, SIGNAL(searchUpdate()), this, SLOT(setupNetworkUpdateSearch1()));
	disconnect(NetworkPlr, SIGNAL(connectComplete()), this, SLOT(setupNetworkUpdateSearch2()));
	disconnect(next_btn, SIGNAL(clicked()), this, SLOT(setupNetworkGetSearch()));
	settingsBox->findChild<QLabel*>("Network Search Label")->hide();
	settingsBox->findChild<QComboBox*>("Network Search")->hide();
	QString choosedIP = settingsBox->findChild<QComboBox*>("Network Search")->currentText();
	NetworkPlr->createClient(choosedIP);
	// end
	qDebug() << "get search";
	setupNetworkEnd();
}

void View_StartGame::setupPlayerEndSlot(Player *p) {
	settingsBox->hide();
	disconnect(this, SIGNAL(setupPlayerEndSignal(Player*)), this, SLOT(setupPlayerEndSlot(Player*)));
	if (curColor == WHITE) {
		wp = p;
		setupPlayerBegin(BLACK);
	} else if (curColor == BLACK) {
		bp = p;
		sendPlayersData();
	} else {
		exit(1);
	}
}

// send data for game creation
void View_StartGame::View_StartGame::sendPlayersData() {
	emit createGame(wp, bp);
}

// show first screen
void View_StartGame::show() {
	// greeting box
	greeting = new QFrame(window);
	greeting->setGeometry(40, 40, 720, 340);
	greeting->setFrameStyle(QFrame::Box | QFrame::Plain);
	greeting->setLineWidth(3);
	greeting->show();
	
	// choose white player
	QGroupBox *plr1 = new QGroupBox(greeting);
	plr1->setObjectName("White player");
	plr1->setGeometry(10, 5, 340, 270);
	QLabel *plr1_Label = new QLabel("White player");
	QRadioButton *plr1_Human = new QRadioButton("Human");
	QRadioButton *plr1_Ai = new QRadioButton("Computer");
	QRadioButton *plr1_Network = new QRadioButton("Network");
	plr1_Human->setChecked(true);
	QVBoxLayout *plr1_Layout = new QVBoxLayout;
	plr1_Layout->addWidget(plr1_Label);
	plr1_Layout->addWidget(plr1_Human);
	plr1_Layout->addWidget(plr1_Ai);
	plr1_Layout->addWidget(plr1_Network);
	plr1->setLayout(plr1_Layout);
	plr1->show();
	
	// choose black player
	QGroupBox *plr2 = new QGroupBox(greeting);
	plr2->setObjectName("Black player");
	plr2->setGeometry(360, 5, 340, 270);
	QLabel *plr2_Label = new QLabel("Black player", plr2);
	QRadioButton *plr2_Human = new QRadioButton("Human", plr2);
	QRadioButton *plr2_Ai = new QRadioButton("Computer", plr2);
	QRadioButton *plr2_Network = new QRadioButton("Network", plr2);
	plr2_Ai->setChecked(true);
	QVBoxLayout *plr2_Layout = new QVBoxLayout;
	plr2_Layout->addWidget(plr2_Label);
	plr2_Layout->addWidget(plr2_Human);
	plr2_Layout->addWidget(plr2_Ai);
	plr2_Layout->addWidget(plr2_Network);
	plr2->setLayout(plr2_Layout);
	plr2->show();
	
	// start game button
	QPushButton *start_btn = new QPushButton("Start game!", greeting);
	start_btn->setGeometry(260, 280, 200, 45);
	start_btn->show();
	connect(start_btn, SIGNAL(clicked()), SLOT(startGame()));
}


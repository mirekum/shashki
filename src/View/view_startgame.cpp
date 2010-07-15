#include "View/view_startgame.h"

View_StartGame::View_StartGame(View_Main &main_ui) {
	window = main_ui.getWindow();
}

// set up players dialog
void View_StartGame::startGame() {
	// set white player type
	QList<QRadioButton*> wLst = greeting->findChild<QGroupBox*>("White player")->findChildren<QRadioButton*>();
	if (wLst.at(0)->isChecked()) wPlr = HUMAN;
	else if (wLst.at(1)->isChecked()) wPlr = AI;
	//else if (wLst.at(2)->isChecked()) wPlr = NETWORK;
	//else if (wLst.at(3)->isChecked()) wPlr = BLUETOOTH;
	
	// set black player type
	QList<QRadioButton*> bLst = greeting->findChild<QGroupBox*>("Black player")->findChildren<QRadioButton*>();
	if (bLst.at(0)->isChecked()) bPlr = HUMAN;
	else if (bLst.at(1)->isChecked()) bPlr = AI;
	//else if (bLst.at(2)->isChecked()) bPlr = NETWORK;
	//else if (bLst.at(3)->isChecked()) bPlr = BLUETOOTH;
	
	greeting->hide();
	playersSettings();
}

void View_StartGame::playersSettings(COLOR color) {
	curColor = color;
	
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
	
	// settings for player
	switch (color == WHITE ? wPlr : bPlr) {
		case HUMAN:
			getPlrSettings();
			return;
		break;
		case AI:
			// AI level
			QGroupBox *ai_level = new QGroupBox(settings);
			ai_level->setObjectName("Ai level");
			ai_level->setGeometry(180, 40, 360, 240);
			QLabel *ai_level_Label = new QLabel("Ai Level:");
			QRadioButton *ai_level_Lvl1 = new QRadioButton("Easy");
			QRadioButton *ai_level_Lvl2 = new QRadioButton("Medium");
			QRadioButton *ai_level_Lvl3 = new QRadioButton("Hard");
			ai_level_Lvl2->setChecked(true);
			QVBoxLayout *ai_level_Layout = new QVBoxLayout;
			ai_level_Layout->addWidget(ai_level_Label);
			ai_level_Layout->addWidget(ai_level_Lvl1);
			ai_level_Layout->addWidget(ai_level_Lvl2);
			ai_level_Layout->addWidget(ai_level_Lvl3);
			ai_level->setLayout(ai_level_Layout);
			ai_level->show();
		break;
	}
	
	// ok button
	QPushButton *ok_btn = new QPushButton("OK!", settings);
	ok_btn->setGeometry(260, 280, 200, 45);
	ok_btn->show();
	connect(ok_btn, SIGNAL(clicked()), SLOT(getPlrSettings()));
}

// get player settings
void View_StartGame::getPlrSettings() {
	PLAYER_TYPE *plr = curColor == WHITE ? &wPlr : &bPlr;
	PLAYER_SETTINGS *set = curColor == WHITE ? &wSet : &bSet;
	
	switch (*plr) {
		case AI:
			QList<QRadioButton*> ai_level = settingsBox->findChild<QGroupBox*>("Ai level")->findChildren<QRadioButton*>();
			if (ai_level.at(0)->isChecked()) set->aiLevel = 2;
			else if (ai_level.at(1)->isChecked()) set->aiLevel = 4;
			else if (ai_level.at(2)->isChecked()) set->aiLevel = 8;
		break;
	}
	
	settingsBox->hide();
	if (curColor == WHITE)
		playersSettings(BLACK);
	else
		sendPlayersData();
}

// send data for game creation
void View_StartGame::sendPlayersData() {
	emit createGame(wPlr, wSet, bPlr, bSet);
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
	//QRadioButton *plr1_Network = new QRadioButton("Network");
	//QRadioButton *plr1_Bluetooth = new QRadioButton("Bluetooth");
	plr1_Human->setChecked(true);
	QVBoxLayout *plr1_Layout = new QVBoxLayout;
	plr1_Layout->addWidget(plr1_Label);
	plr1_Layout->addWidget(plr1_Human);
	plr1_Layout->addWidget(plr1_Ai);
	//plr1_Layout->addWidget(plr1_Network);
	//plr1_Layout->addWidget(plr1_Bluetooth);
	plr1->setLayout(plr1_Layout);
	plr1->show();
	
	// choose black player
	QGroupBox *plr2 = new QGroupBox(greeting);
	plr2->setObjectName("Black player");
	plr2->setGeometry(360, 5, 340, 270);
	QLabel *plr2_Label = new QLabel("Black player", plr2);
	QRadioButton *plr2_Human = new QRadioButton("Human", plr2);
	QRadioButton *plr2_Ai = new QRadioButton("Computer", plr2);
	//QRadioButton *plr2_Network = new QRadioButton("Network", plr2);
	//QRadioButton *plr2_Bluetooth = new QRadioButton("Bluetooth", plr2);
	plr2_Ai->setChecked(true);
	QVBoxLayout *plr2_Layout = new QVBoxLayout;
	plr2_Layout->addWidget(plr2_Label);
	plr2_Layout->addWidget(plr2_Human);
	plr2_Layout->addWidget(plr2_Ai);
	//plr2_Layout->addWidget(plr2_Network);
	//plr2_Layout->addWidget(plr2_Bluetooth);
	plr2->setLayout(plr2_Layout);
	plr2->show();
	
	// start game button
	QPushButton *start_btn = new QPushButton("Start game!", greeting);
	start_btn->setGeometry(260, 280, 200, 45);
	start_btn->show();
	connect(start_btn, SIGNAL(clicked()), SLOT(startGame()));
}


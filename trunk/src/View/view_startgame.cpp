#include "View/view_startgame.h"

View_StartGame::View_StartGame(View_Main &_main_ui) {
	main_ui = _main_ui;
	window = main_ui->getWindow();
}

// show first screen
void View_StartGame::show() {
	// greeting box
	QFrame *greeting = new QFrame(window);
	greeting->move(40, 40);
	greeting->resize(720, 340);
	greeting->setFrameStyle(QFrame::Box | QFrame::Plain);
	greeting->setLineWidth(3);
	greeting->show();
	
	// choose white player
	QGroupBox *plr1 = new QGroupBox(greeting);
	plr1->setGeometry(10, 5, 340, 270);
	QLabel *plr1_Label = new QLabel("White player", plr1);
	QRadioButton *plr1_Human = new QRadioButton("Human", plr1);
	QRadioButton *plr1_Ai = new QRadioButton("Computer", plr1);
	QRadioButton *plr1_Network = new QRadioButton("Network", plr1);
	QRadioButton *plr1_Bluetooth = new QRadioButton("Bluetooth", plr1);
	plr1_Human->setChecked(true);
	QVBoxLayout *plr1_Layout = new QVBoxLayout;
	plr1_Layout->addWidget(plr1_Label);
	plr1_Layout->addWidget(plr1_Human);
	plr1_Layout->addWidget(plr1_Ai);
	plr1_Layout->addWidget(plr1_Network);
	plr1_Layout->addWidget(plr1_Bluetooth);
	plr1->setLayout(plr1_Layout);
	plr1->show();
	
	// choose black player
	QGroupBox *plr2 = new QGroupBox(greeting);
	plr2->setGeometry(360, 5, 340, 270);
	QLabel *plr2_Label = new QLabel("Black player", plr2);
	QRadioButton *plr2_Human = new QRadioButton("Human", plr2);
	QRadioButton *plr2_Ai = new QRadioButton("Computer", plr2);
	QRadioButton *plr2_Network = new QRadioButton("Network", plr2);
	QRadioButton *plr2_Bluetooth = new QRadioButton("Bluetooth", plr2);
	plr2_Ai->setChecked(true);
	QVBoxLayout *plr2_Layout = new QVBoxLayout;
	plr2_Layout->addWidget(plr2_Label);
	plr2_Layout->addWidget(plr2_Human);
	plr2_Layout->addWidget(plr2_Ai);
	plr2_Layout->addWidget(plr2_Network);
	plr2_Layout->addWidget(plr2_Bluetooth);
	plr2->setLayout(plr2_Layout);
	plr2->show();
	
	// start game button
	QPushButton *start_btn = new QPushButton("Start game!", greeting);
	start_btn->setGeometry(260, 280, 200, 45);
	start_btn->show();
}


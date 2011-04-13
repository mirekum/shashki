#include "control.h"

// create application
Control::Control(int &argc, char** argv):QApplication(argc, argv) {
	qDebug() << "run Qt Application";
	
	// link to model
	game = 0;
	
	// create views
	main_ui = new View_Main;
	start_ui = new View_StartGame(main_ui);
	board_ui = new View_Board(main_ui);
	info_ui = new View_Info(main_ui);
	finish_ui = new View_FinishGame(main_ui);
	qDebug() << "all views created";
	
	// show application
	main_ui->show();
	qDebug() << "main UI showed";
	
	// signal to start game
	connect(this, SIGNAL(newGameSignal()), this, SLOT(newGame()));
	connect(main_ui, SIGNAL(newGameSignal()), this, SLOT(newGame()));
	
	// start first game
	emit newGameSignal();
	
	qDebug() << "Application has been run";
}

void Control::newGame() {
	qDebug() << "try to start new game";
	
	// finish game if need
	if (game) emit finishGame(END_DRAW);
	
	// signal to create game
	connect(start_ui, SIGNAL(createGame(Player*, Player*)), this, SLOT(createGame(Player*, Player*)));
	
	// signal to quit game
	connect(main_ui, SIGNAL(quit()), this, SLOT(quit()));
	
	// hide UIs
	board_ui->hide();
	info_ui->hide();
	finish_ui->hide();
	
	// show start dialog
	start_ui->show();
	
	qDebug() << "new game started";
}

void Control::createGame(Player *wp, Player *bp) {
	qDebug() << "try to create new game";
	
	// disconnect signal to create game
	disconnect(start_ui, SIGNAL(createGame(Player*, Player*)), this, SLOT(createGame(Player*, Player*)));
	
	// create game
	game = new Game;
	qDebug() << "game created";
	
	// signals to finish game
	connect(game, SIGNAL(finishGame(GAMESTATE)), this, SLOT(finishGame(GAMESTATE)));
	connect(main_ui, SIGNAL(finishGame(GAMESTATE)), this, SLOT(finishGame(GAMESTATE)));
	
	// players
	if (wp == NULL) wp = board_ui;
	if (bp == NULL) bp = board_ui;
	qDebug() << "players initialized";
	
	// model initialization
	game->init(wp, bp);
	qDebug() << "game initialized";
	
	// game views initialization
	board_ui->init(game);
	info_ui->init(game);
	qDebug() << "views initialized";
	
	// start game
	qDebug() << "game->start();";
	game->start();
}

void Control::finishGame(GAMESTATE res_flag) {
	qDebug() << "try to finish current game";
	
	if (!game) {
		qDebug() << "can not finish current game (game has been already finished)";
		return;
	}
	
	// disconnect signals to finish game
	disconnect(game, SIGNAL(finishGame(GAMESTATE)), this, SLOT(finishGame(GAMESTATE)));
	disconnect(main_ui, SIGNAL(finishGame(GAMESTATE)), this, SLOT(finishGame(GAMESTATE)));
	
	// game views hiding
	info_ui->hide();
	
	// finish game
	finish_ui->showResult(res_flag);
	
	// destroy game
	delete game;
	game = 0;
	qDebug() << "game destroyed";
}

// close (destroy) application
Control::~Control() {
	qDebug() << "Control::~Control() -> BEGIN";
	
	delete main_ui;
	
	qDebug() << "Control::~Control() -> END";
}


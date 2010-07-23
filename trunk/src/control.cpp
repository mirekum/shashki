#include "control.h"

Control::Control(Game &_game, View_Main &_main_ui, View_StartGame &_start_ui, View_FinishGame &_finish_ui, View_Board &_board_ui, View_Info &_info_ui) {
	// model
	game = &_game;
	// views
	main_ui = &_main_ui;
	start_ui = &_start_ui;
	finish_ui = &_finish_ui;
	board_ui = &_board_ui;
	info_ui = &_info_ui;
	
	// signal to create game
	connect(start_ui, SIGNAL(createGame(Player*, Player*)), SLOT(createGame(Player*, Player*)));
	// signal to start game
	connect(this, SIGNAL(startGameSignal()), SLOT(startGameSlot()));
	// signal to finish game
	connect(game, SIGNAL(finishGame(GAMESTATE)), SLOT(finishGame(GAMESTATE)));
}

void Control::createGame(Player *wp, Player *bp) {
	if (wp == NULL) wp = board_ui;
	if (bp == NULL) bp = board_ui;
	// model initialization
	game->init(wp, bp);
	// game views initialization
	board_ui->init(game);
	info_ui->init(game);
	// start game
	emit startGameSignal();
}

void Control::startGameSlot() {
	game->start();
}

void Control::finishGame(GAMESTATE res_flag) {
	// game views hiding
	info_ui->hide();
	// finish game
	finish_ui->show(res_flag);
}


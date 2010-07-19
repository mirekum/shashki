#include "control.h"
#include "Players/ai_player.h"
#include "Players/bluetooth_player.h"
#include "Players/network_player.h"

Control::Control(Game &_game, View_Main &_main_ui, View_StartGame &_start_ui, View_Board &_board_ui, View_Info &_info_ui) {
	// model
	game = &_game;
	// views
	main_ui = &_main_ui;
	start_ui = &_start_ui;
	board_ui = &_board_ui;
	info_ui = &_info_ui;
	
	// signal to create game
	connect(start_ui, SIGNAL(createGame(Player*, Player*)), SLOT(createGame(Player*, Player*)));
}

void Control::createGame(Player *wp, Player *bp) {
	if (wp == NULL) wp = board_ui;
	if (bp == NULL) bp = board_ui;
	// model initialization
	game->init(wp, bp);
	// game views initialization
	board_ui->init(game);
	info_ui->init(game);
}


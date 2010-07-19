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
	connect(start_ui,
		SIGNAL(createGame(PLAYER_TYPE, PLAYER_SETTINGS, PLAYER_TYPE, PLAYER_SETTINGS)),
		SLOT(createGame(PLAYER_TYPE, PLAYER_SETTINGS, PLAYER_TYPE, PLAYER_SETTINGS))
	);
}

void Control::createGame(PLAYER_TYPE wPlr, PLAYER_SETTINGS wSet, PLAYER_TYPE bPlr, PLAYER_SETTINGS bSet) {
	wp = createPlayer(wPlr, wSet);
	bp = createPlayer(bPlr, bSet);
	// model initialization
	game->init(wp, bp);
	// game views initialization
	board_ui->init(game);
	info_ui->init(game);
}

Player *Control::createPlayer(PLAYER_TYPE plr, PLAYER_SETTINGS set) {
	switch (plr) {
		case HUMAN:
			return board_ui;
		case AI:
			return new Ai_Player(set.aiLevel);
		case NETWORK:
			return new Network_Player();
		case BLUETOOTH:
			return new Bluetooth_Player();
		default:
			exit(1);
	}
}

void Control::destroyPlayer(Player *p) {
	if (p->type() != HUMAN) delete p;
}

Control::~Control() {
	destroyPlayer(wp);
	destroyPlayer(bp);
}


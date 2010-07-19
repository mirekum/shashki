#include "Model/game.h"
#include "Players/ai_player.h"
#include "Players/network_player.h"
#include "Players/bluetooth_player.h"
#include "View/view_board.h"

Game::Game() {
	wp = NULL;
	bp = NULL;
}

void Game::init(Player *_wp, Player *_bp) {
	if (!_wp || !_bp) exit(1);
	wp = _wp;
	bp = _bp;
}

BOARD& Game::getBoard() {
	return board;
}


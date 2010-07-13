#include "Model/game.h"
#include "Players/ai.h"
#include "Players/network.h"
#include "Players/bluetooth.h"

Game::Game() {
	wp = NULL;
	bp = NULL;
}

Game::~Game() {
	delete wp;
	delete bp;
}

BOARD& Game::getBoard() {
	return board;
}


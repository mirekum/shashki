#include "View/view_board.h"

View_Board::View_Board(View_Main &main_ui, Game &_game) {
	window = main_ui.getWindow();
	game = &_game;
}

// get move from human
MOVE View_Board::getMove(BOARD board) {
	
}


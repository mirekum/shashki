#include "View/view_board.h"

View_Board::View_Board(View_Main &_main_ui) {
	main_ui = _main_ui;
	window = main_ui->getWindow();
}

// get move from human
MOVE View_Board::getMove(BOARD board) {
	
}


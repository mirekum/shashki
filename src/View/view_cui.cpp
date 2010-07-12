#include <QApplication>
#include "View/view_cui.h"

/* methods of the CUI view class */

// create game instance (H-H, H-A, H-N, etc)
GAME* VIEW_CUI::createGame() {
	// here you can ask user about which game he wants to play
	// because of GUI is main interface this step was skipped for CUI
	return new GAME(HUMAN, AI);
}

// exec game process
int VIEW_CUI::gameProcess() {
	GAMESTATE res_flag;
	VIEW_CUI::Input gameInput;
	
	game->start(gameInput);
	
	do {
		std::cout << "*** ХОД БЕЛЫХ ***" << std::endl;
		std::cout << game->getBoard() << std::endl;
		game->startMove(WHITE);
		do {
			game->execMove();
		}
		while (game->canMove());
		if (res_flag = game->checkResult()) goto result;
		
		std::cout << "*** ХОД ЧЁРНЫХ ***" << std::endl;
		std::cout << game->getBoard() << std::endl;
		game->startMove(BLACK);
		do {
			game->execMove();
		}
		while (game->canMove());
		if (res_flag = game->checkResult()) goto result;
		
		std::cout << std::endl;
	} while(1);
	
	result:
	game->finish();
	
	gameResults(res_flag);
	
	return 0;
}

// get move from human player
MOVE VIEW_CUI::Input::humanGetmove(BOARD board) {
	MOVE result;
	
	do {
		std::cout << "x1 = "; std::cin >> result.from.x;
		std::cout << "y1 = "; std::cin >> result.from.y;
		std::cout << "x2 = "; std::cin >> result.to.x;
		std::cout << "y2 = "; std::cin >> result.to.y;
		if (board.move(result)) break;
		else std::cout << "Ошибка! Повторите ввод!" << std::endl;
	} while (1);
	
	return result;
}

// show results of the game
void VIEW_CUI::gameResults(GAMESTATE res_flag) {
	std::cout << game->getBoard() << std::endl;
	switch(res_flag) {
		case END_WHITE:
			std::cout << "\n\n********** БЕЛЫЕ ВЫИГРАЛИ **********\n\n" << std::endl;
		break;
		case END_BLACK:
			std::cout << "\n\n********** ЧЁРНЫЕ ВЫИГРАЛИ **********\n\n" << std::endl;
		break;
		case END_DRAW:
			std::cout << "\n\n***** НИЧЬЯ *****\n\n" << std::endl;
		break;
	}
}

// print the board on the screen
std::ostream& operator<< (std::ostream &cout, BOARD &board) {
	std::cout << "------ Доска ------" << std::endl;
	std::cout << "   0 1 2 3 4 5 6 7 " << std::endl << std::endl;
	for (int y = 0; y < board.size; y++) {
		std::cout << y << "  ";
		for (int x = 0; x < board.size; x++) {
			if (board.gcell(x, y) == WHITE_PAWN)
				std::cout << "x ";
			else if (board.gcell(x, y) == BLACK_PAWN)
				std::cout << "o ";
			else if (board.gcell(x, y) == WHITE_KING)
				std::cout << "W ";
			else if (board.gcell(x, y) == BLACK_KING)
				std::cout << "B ";
			else
				std::cout << "  ";
		}
		std::cout << std::endl;
	}
	std::cout << "-------------------";
	return std::cout;
}


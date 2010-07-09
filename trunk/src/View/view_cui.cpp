#include <QApplication>
#include "View/view_cui.h"

/* methods of the CUI view class */

// create game instance (H-H, H-A, H-N, etc)
GAME* VIEW_CUI::createGame() {
	return new GAME(HUMAN, AI);
}

// exec game process
int VIEW_CUI::gameProcess() {
	GAMESTATE res_flag;
	
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


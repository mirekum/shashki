#include <iostream>
#include "board.h"
#include "human.h"

/* mathods of class of the human player */

// chooses partial half-move
MOVE HUMAN_PLAYER::getMove(BOARD board) {
	// request partial half-move
	do {
		std::cout << "x1 = "; std::cin >> PLAYER::result.from.x;
		std::cout << "y1 = "; std::cin >> PLAYER::result.from.y;
		std::cout << "x2 = "; std::cin >> PLAYER::result.to.x;
		std::cout << "y2 = "; std::cin >> PLAYER::result.to.y;
		if (board.move(PLAYER::result)) break;
		else std::cout << "Ошибка! Повторите ввод!" << std::endl;
	} while (1);
	
	return PLAYER::result;
}


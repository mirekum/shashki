#include <iostream>
#include "board.h"
#include "human.h"

/* mathods of class of the human player */

// chooses partial half-move
MOVE HUMAN_PLAYER::get_move(BOARD board) {
	MOVE res;
	
	// request partial half-move
	do {
		std::cout << "x1 = "; std::cin >> res.from.x;
		std::cout << "y1 = "; std::cin >> res.from.y;
		std::cout << "x2 = "; std::cin >> res.to.x;
		std::cout << "y2 = "; std::cin >> res.to.y;
		if (board.move(res)) break;
		else std::cout << "Ошибка! Повторите ввод!" << std::endl;
	} while (1);
	
	return res;
}


#include <iostream>
#include "board.h"
#include "human.h"

/* методы класса "Игрок-человек" */

// выполнение хода
MOVE HUMAN_PLAYER::move(BOARD board) {
	// неполный полуход
	MOVE res;
	// вводим неполный полуход
	do {
		std::cout << "x1 = "; std::cin >> res.from.x;
		std::cout << "y1 = "; std::cin >> res.from.y;
		std::cout << "x2 = "; std::cin >> res.to.x;
		std::cout << "y2 = "; std::cin >> res.to.y;
		if (board.move(res)) break;
		else std::cout << "Error, please repeat move!" << std::endl;
	} while (1);
	// результат
	return res;
}


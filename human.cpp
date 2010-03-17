#include <iostream>

#include "board.h"
#include "player.h"
#include "human.h"
#include "game.h"

using namespace std;

/* методы класса "Игрок-человек" */

// выполнение хода
MOVE HUMAN_PLAYER::move(BOARD board) {
	// неполный полуход
	MOVE res;
	// вводим неполный полуход
	do {
		cout << "x1 = "; cin >> res.from.x;
		cout << "y1 = "; cin >> res.from.y;
		cout << "x2 = "; cin >> res.to.x;
		cout << "y2 = "; cin >> res.to.y;
		if (board.move(res)) break;
		else cout << "Error, please repeat move!" << endl;
	} while (1);
	// результат
	return res;
}


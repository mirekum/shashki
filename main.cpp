#include <QtTest/QtTest>
#include "game.h"
#include "test_board.h"

// entry point
int main () {
	Test_Board test_board;
	QTest::qExec(&test_board);
	
	GAME shashki(AI, HUMAN);
	return 0;
}


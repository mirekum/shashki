#include <QObject>
#include <QtTest/QtTest>
#include "board.h"

class Test_Board : public QObject {
	Q_OBJECT
	
	private slots:
		void test_moves_func();
		void test_king_moves();
		void test_difficult_moves();
		void test_simple_moves();
		void test_set_get_cell();
		void test_getColor();
};


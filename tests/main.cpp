#include <QtCore>
#include "experiment.h"
#include "test_board.h"

// entry point
int main(int argc, char** argv) {
	// board test
	Test_Board boardTest;
	QTest::qExec(&boardTest);
	
	
	// exit
	return 0;
}


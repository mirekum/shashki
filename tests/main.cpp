#include <QtCore>
#include "experiment.h"
#include "test_board.h"

// entry point
int main(int argc, char** argv) {
	// board test
	Test_Board test1;
	QTest::qExec(&test1);
	
	// exit
	return 0;
}


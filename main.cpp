#include "game.h"
#include <cppunit/ui/text/TestRunner.h>
#include "board_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(board_test);

// entry point
int main () {
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	runner.run();
	GAME shashki(HUMAN, AI);
	return 0;
}
	

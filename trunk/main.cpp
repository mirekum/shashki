#include "game.h"
#include <cppunit/ui/text/TestRunner.h>
#include "board_test.h"

#define DEBUG

#ifdef DEBUG
	CPPUNIT_TEST_SUITE_REGISTRATION(board_test);
#endif

// entry point
int main () {
#ifdef DEBUG
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	runner.run();
#endif
	GAME shashki(HUMAN, AI);
	return 0;
}
	

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "board.h"

class board_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(board_test);
	CPPUNIT_TEST(test_move1);
	CPPUNIT_TEST(test_set_get_cell);
	CPPUNIT_TEST(test_getColor);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp() {
		
	}
	void tearDown() {
		
	}
	// test different moves
	void test_move1() {
		BOARD board;
		
		board.startMove(WHITE);
		CPPUNIT_ASSERT(board.canMove());
		board.move(6, 5, 5, 4);
		CPPUNIT_ASSERT(board.gcell(5, 4) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.gcell(6, 5) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		board.startMove(BLACK);
		CPPUNIT_ASSERT(board.canMove());
		board.move(5, 2, 4, 3);
		CPPUNIT_ASSERT(board.gcell(4, 3) == BLACK_PAWN);
		CPPUNIT_ASSERT(board.gcell(5, 2) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		board.startMove(WHITE);
		CPPUNIT_ASSERT(board.canMove());
		board.move(5, 4, 6, 3);
		CPPUNIT_ASSERT(board.gcell(6, 3) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.gcell(5, 4) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		board.startMove(BLACK);
		CPPUNIT_ASSERT(board.canMove());
		// TODO: write test for moves function
		board.move(7, 2, 5, 4);
		CPPUNIT_ASSERT(board.gcell(5, 4) == BLACK_PAWN);
		CPPUNIT_ASSERT(board.gcell(7, 2) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(6, 3) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		// TODO: write further tests
	}
	// test scell and getcell
	void test_set_get_cell() {
		BOARD board;
		CPPUNIT_ASSERT(board.gcell(-1, -1) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(board.size, board.size) == EMPTY);
		
		CPPUNIT_ASSERT(board.gcell(0, 0) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(7, 7) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(7, 0) == BLACK_PAWN);
		CPPUNIT_ASSERT(board.gcell(7, 2) == BLACK_PAWN);
		CPPUNIT_ASSERT(board.gcell(0, 7) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.gcell(0, 5) == WHITE_PAWN);
		
		CPPUNIT_ASSERT(!board.scell(-1, -1, EMPTY));
		CPPUNIT_ASSERT(!board.scell(board.size, board.size, EMPTY));
		
		CPPUNIT_ASSERT(board.scell(1, 0, EMPTY));
		CPPUNIT_ASSERT(board.gcell(1, 0) == EMPTY);
		CPPUNIT_ASSERT(board.scell(2, 7, EMPTY));
		CPPUNIT_ASSERT(board.gcell(2, 7) == EMPTY);
		
		CPPUNIT_ASSERT(board.scell(1, 0, WHITE_PAWN));
		CPPUNIT_ASSERT(board.gcell(1, 0) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.scell(2, 7, BLACK_PAWN));
		CPPUNIT_ASSERT(board.gcell(2, 7) == BLACK_PAWN);
	}
	// test getColor function
	void test_getColor() {
		CPPUNIT_ASSERT(getColor(BLACK_KING) == BLACK);
		CPPUNIT_ASSERT(getColor(BLACK_PAWN) == BLACK);
		CPPUNIT_ASSERT(getColor(EMPTY) == NONE);
		CPPUNIT_ASSERT(getColor(WHITE_PAWN) == WHITE);
		CPPUNIT_ASSERT(getColor(WHITE_KING) == WHITE);
	}
};


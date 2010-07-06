#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "board.h"

class board_test : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(board_test);
	CPPUNIT_TEST(test_moves_func);
	CPPUNIT_TEST(test_king_moves);
	CPPUNIT_TEST(test_difficult_moves);
	CPPUNIT_TEST(test_simply_moves);
	CPPUNIT_TEST(test_set_get_cell);
	CPPUNIT_TEST(test_getColor);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp() {
		
	}
	void tearDown() {
		
	}
	// moves function
	void test_moves_func() {
		BOARD board;
		CANMOVE cmFlag;
		for (int i = 0; i < board.size; i++) {
			for (int j = 0; j < board.size; j++) {
				board.scell(i, j, EMPTY);
			}
		}
		board.scell(2, 5, WHITE_PAWN);
		board.scell(5, 2, WHITE_PAWN);
		board.scell(1, 2, WHITE_KING);
		board.scell(6, 5, WHITE_KING);
		board.scell(1, 4, BLACK_PAWN);
		board.scell(3, 6, BLACK_KING);
		board.scell(5, 4, BLACK_PAWN);
		board.scell(3, 2, BLACK_KING);
		board.scell(3, 0, BLACK_PAWN);
		board.scell(7, 0, BLACK_KING);
		board.scell(5, 6, BLACK_PAWN);
		
		std::cout << board << std::endl;
		
		board.startMove(WHITE);
		CPPUNIT_ASSERT(board.canMove());
		
		CELL m[16]; int n;
		CPPUNIT_ASSERT(n = board.moves(CELL(2, 5), m));
		std::cout << "moves from 2,5:" << std::endl;
		for (int i = 0; i < n; i++) {
			std::cout << m[i].x << "," << m[i].y << std::endl;
		}
		
		std::cout << "moves from 5,2:" << std::endl;
		CPPUNIT_ASSERT(!board.moves(CELL(5, 2), m));
		
		std::cout << "moves from 1,2:" << std::endl;
		CPPUNIT_ASSERT(n = board.moves(CELL(1, 2), m));
		for (int i = 0; i < n; i++) {
			std::cout << m[i].x << "," << m[i].y << std::endl;
		}
		
		std::cout << "moves from 6,5:" << std::endl;
		CPPUNIT_ASSERT(n = board.moves(CELL(6, 5), m));
		for (int i = 0; i < n; i++) {
			std::cout << m[i].x << "," << m[i].y << std::endl;
		}
		
		std::cout << board << std::endl;
	}
	// test different moves
	void test_king_moves() {
		BOARD board;
		CANMOVE cmFlag;
		for (int i = 0; i < board.size; i++) {
			for (int j = 0; j < board.size; j++) {
				board.scell(i, j, EMPTY);
			}
		}
		board.scell(1, 4, BLACK_PAWN);
		board.scell(2, 5, BLACK_PAWN);
		board.scell(5, 4, BLACK_PAWN);
		board.scell(6, 5, BLACK_PAWN);
		board.scell(1, 6, BLACK_KING);
		board.scell(5, 2, BLACK_KING);
		board.scell(4, 7, WHITE_KING);
		
		board.startMove(WHITE);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(!board.canMove(4, 7, 3, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 2, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 1, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 0, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 2, 7, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 6, 7, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 5, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 6, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 4, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 7, 4, 6, NULL, WHITE));
		CPPUNIT_ASSERT(board.canMove(4, 7, 7, 4, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 5 && cmFlag.king == NONE);
		board.move(4, 7, 7, 4);
		CPPUNIT_ASSERT(board.gcell(7, 4) == WHITE_KING);
		CPPUNIT_ASSERT(board.gcell(6, 5) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(4, 7) == EMPTY);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(board.canMove(7, 4, 4, 1, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 5 && cmFlag.eat_c.y == 2 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(7, 4, 6, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 4, 7, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 4, 6, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 4, 5, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 4, 4, 7, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 4, 3, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 4, 5, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 4, 5, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 4, 4, 3, NULL, WHITE));
		board.move(7, 4, 4, 1);
		CPPUNIT_ASSERT(board.gcell(4, 1) == WHITE_KING);
		CPPUNIT_ASSERT(board.gcell(7, 4) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(5, 2) == EMPTY);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(board.canMove(4, 1, 0, 5, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 1 && cmFlag.eat_c.y == 4 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(4, 1, 5, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 3, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 7, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 1, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 4, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 5, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 6, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 7, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 7, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 3, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 2, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 1, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 0, 3, NULL, WHITE));
		board.move(4, 1, 0, 5);
		CPPUNIT_ASSERT(board.gcell(0, 5) == WHITE_KING);
		CPPUNIT_ASSERT(board.gcell(4, 1) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(1, 4) == EMPTY);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(board.canMove(0, 5, 2, 7, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 1 && cmFlag.eat_c.y == 6 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(0, 5, 1, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 0, 7, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 3, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 4, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 2, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 1, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 0, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 2, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 3, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 4, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 5, 0, NULL, WHITE));
		board.move(0, 5, 2, 7);
		CPPUNIT_ASSERT(board.gcell(2, 7) == WHITE_KING);
		CPPUNIT_ASSERT(board.gcell(0, 5) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(1, 6) == EMPTY);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(board.canMove(2, 7, 6, 3, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 5 && cmFlag.eat_c.y == 4 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(2, 7, 1, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 0, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 0, 7, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 4, 7, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 3, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 4, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 5, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 7, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 7, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 7, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 6, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(2, 7, 4, 3, NULL, WHITE));
		board.move(2, 7, 6, 3);
		CPPUNIT_ASSERT(board.gcell(6, 3) == WHITE_KING);
		CPPUNIT_ASSERT(board.gcell(2, 7) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(5, 4) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
	}
	void test_difficult_moves() {
		BOARD board;
		CANMOVE cmFlag;
		for (int i = 0; i < board.size; i++) {
			for (int j = 0; j < board.size; j++) {
				board.scell(i, j, EMPTY);
			}
		}
		board.scell(4, 1, BLACK_PAWN);
		board.scell(6, 1, BLACK_PAWN);
		board.scell(4, 3, BLACK_KING);
		board.scell(6, 3, BLACK_KING);
		board.scell(6, 5, BLACK_PAWN);
		board.scell(2, 3, BLACK_PAWN);
		board.scell(2, 5, BLACK_PAWN);
		board.scell(4, 5, BLACK_PAWN);
		board.scell(5, 6, BLACK_PAWN);
		board.scell(1, 6, WHITE_PAWN);
		
		board.startMove(WHITE);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(!board.canMove(1, 6, 2, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 6, 0, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 6, 2, 7, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 6, 0, 7, NULL, WHITE));
		CPPUNIT_ASSERT(board.canMove(1, 6, 3, 4, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 2 && cmFlag.eat_c.y == 5 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(1, 6, 1, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 6, 3, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 6, 5, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 6, 1, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 6, 6, 7, NULL, WHITE));
		board.move(1, 6, 3, 4);
		CPPUNIT_ASSERT(board.gcell(3, 4) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.gcell(1, 6) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(2, 5) == EMPTY);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(board.canMove(3, 4, 1, 2, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 2 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(board.canMove(3, 4, 5, 2, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 4 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(3, 4, 0, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 4, 2, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 4, 1, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 4, 4, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 4, 5, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 4, 6, 7, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 4, 7, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 4, 7, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 4, 3, 0, NULL, WHITE));
		board.move(3, 4, 5, 2);
		CPPUNIT_ASSERT(board.gcell(5, 2) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.gcell(3, 4) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(4, 3) == EMPTY);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(board.canMove(5, 2, 3, 0, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 4 && cmFlag.eat_c.y == 1 && cmFlag.king == WHITE);
		CPPUNIT_ASSERT(board.canMove(5, 2, 7, 0, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 1 && cmFlag.king == WHITE);
		CPPUNIT_ASSERT(board.canMove(5, 2, 7, 4, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(5, 2, 4, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 3, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 4, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 6, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 6, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 5, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 7, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 2, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 1, 6, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 0, 7, NULL, WHITE));
		board.move(5, 2, 3, 0);
		CPPUNIT_ASSERT(board.gcell(3, 0) == WHITE_KING);
		CPPUNIT_ASSERT(board.gcell(5, 2) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(4, 1) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove(3, 0, 2, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 0, 1, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 0, 0, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 0, 4, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 0, 5, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 0, 6, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 0, 3, 1, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 0, 7, 0, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 0, 6, 5, NULL, WHITE));
		CPPUNIT_ASSERT(board.canMove(3, 0, 7, 4, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_KING && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
		board.move(3, 0, 7, 4);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
	}
	void test_simply_moves() {
		BOARD board;
		CANMOVE cmFlag;
		
		board.startMove(WHITE);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(board.canMove(0, 5, 1, 4, NULL, WHITE));
		CPPUNIT_ASSERT(board.canMove(2, 5, 1, 4, NULL, WHITE));
		CPPUNIT_ASSERT(board.canMove(2, 5, 3, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 0, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 2, 3, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 2, 2, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(1, 2, 0, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 2, 2, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(3, 2, 4, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 0, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 5, 1, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 1, 0, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(0, 1, 1, 1, NULL, WHITE));
		board.move(6, 5, 5, 4);
		CPPUNIT_ASSERT(board.gcell(5, 4) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.gcell(6, 5) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		board.startMove(BLACK);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(!board.canMove(1, 2, 3, 4, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(1, 2, 0, 3, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(1, 2, 2, 3, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(3, 2, 2, 3, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(3, 2, 4, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 4, 6, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 4, 4, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(2, 5, 1, 4, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(2, 5, 3, 4, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 6, 6, 5, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 6, 7, 4, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(5, 2, 4, 3, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(5, 2, 6, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 3, 4, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 7, 4, NULL, BLACK));
		board.move(5, 2, 4, 3);
		CPPUNIT_ASSERT(board.gcell(4, 3) == BLACK_PAWN);
		CPPUNIT_ASSERT(board.gcell(5, 2) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		board.startMove(WHITE);
		CPPUNIT_ASSERT(board.canMove(5, 4, 6, 3, NULL, WHITE));
		CPPUNIT_ASSERT(board.canMove(2, 5, 1, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 4, 4, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 4, 6, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(5, 4, 4, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 3, 3, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 3, 5, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(7, 2, 6, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 3, 5, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 3, 6, 5, NULL, WHITE));
		CPPUNIT_ASSERT(board.canMove());
		board.move(5, 4, 6, 3);
		CPPUNIT_ASSERT(board.gcell(6, 3) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.gcell(5, 4) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		board.startMove(BLACK);
		CPPUNIT_ASSERT(board.canMove(7, 2, 5, 4, &cmFlag, BLACK));
		CPPUNIT_ASSERT(cmFlag.eat == WHITE_PAWN && cmFlag.eat_c.x == 6 && cmFlag.eat_c.y == 3 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(7, 2, 6, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(7, 2, 7, 4, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(7, 2, 5, 2, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 6, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 2, 4, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(3, 2, 4, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(3, 2, 5, 4, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(3, 2, 1, 4, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(1, 2, 6, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(1, 2, 1, 3, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove());
		board.move(7, 2, 5, 4);
		CPPUNIT_ASSERT(board.gcell(5, 4) == BLACK_PAWN);
		CPPUNIT_ASSERT(board.gcell(7, 2) == EMPTY);
		CPPUNIT_ASSERT(board.gcell(6, 3) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		board.startMove(WHITE);
		CPPUNIT_ASSERT(board.canMove());
		CPPUNIT_ASSERT(board.canMove(4, 5, 6, 3, &cmFlag, WHITE));
		CPPUNIT_ASSERT(cmFlag.eat == BLACK_PAWN && cmFlag.eat_c.x == 5 && cmFlag.eat_c.y == 4 && cmFlag.king == NONE);
		CPPUNIT_ASSERT(!board.canMove(4, 5, 5, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 5, 3, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 5, 7, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 5, 2, 3, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 5, 5, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 5, 7, 4, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 5, 6, 5, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 5, 1, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(6, 1, 7, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 5, 2, NULL, WHITE));
		CPPUNIT_ASSERT(!board.canMove(4, 1, 6, 3, NULL, WHITE));
		board.move(4, 5, 6, 3);
		CPPUNIT_ASSERT(board.gcell(6, 3) == WHITE_PAWN);
		CPPUNIT_ASSERT(board.gcell(4, 5) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
		
		board.startMove(BLACK);
		CPPUNIT_ASSERT(board.canMove(1, 2, 0, 3, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(1, 2, 2, 3, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(6, 1, 5, 2, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(6, 1, 7, 2, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(7, 0, 5, 2, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 0, 6, 1, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(5, 0, 7, 2, NULL, BLACK));
		CPPUNIT_ASSERT(board.canMove(3, 2, 2, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(3, 2, 4, 3, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(6, 3, 5, 2, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(6, 3, 7, 2, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(6, 3, 5, 4, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(6, 3, 7, 4, NULL, BLACK));
		CPPUNIT_ASSERT(!board.canMove(3, 6, 4, 3, NULL, BLACK));
		board.move(1, 2, 0, 3);
		CPPUNIT_ASSERT(board.gcell(0, 3) == BLACK_PAWN);
		CPPUNIT_ASSERT(board.gcell(1, 2) == EMPTY);
		CPPUNIT_ASSERT(!board.canMove());
		CPPUNIT_ASSERT(!board.isWin());
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


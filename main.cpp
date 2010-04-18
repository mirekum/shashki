#include "experiment.h"

// entry point
int main () {
	BOARD board;
	board.scell(1, 2, NONE);
	board.scell(3, 2, NONE);
	board.scell(5, 2, NONE);
	board.scell(7, 2, NONE);
	board.scell(0, 5, NONE);
	board.scell(2, 5, NONE);
	board.scell(4, 5, NONE);
	board.scell(6, 5, NONE);
	board.scell(7, 6, NONE);
	std::cout << board << std::endl;
	
	EXPERIMENT exp(board, PWHITE, 10, 1000, 0.10, 1, 8);
	exp.run(AI_PRL); // 2 threads
	exp.run(AI_PRL2); // 4 threads
	exp.run(AI_SEQ); // sequence
	exp.run(AI_PRL3); // 1 thread
	
	return 0;
}


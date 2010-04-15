#include "experiment.h"

// entry point
int main () {
	BOARD board;
	std::cout << board << std::endl;
	board.start_move(PWHITE);
	
	EXPERIMENT exp(board, 10, 30, 0.10, 2, 10);
	exp.run(AI_PRL,  "parallel ai (2 threads)");
	exp.run(AI_PRL2, "parallel ai (4 threads)");
	exp.run(AI_SEQ,  "sequence ai (1 thread )");
	
	BOARD board2;
	board2.scell(0, 1, NONE);
	board2.scell(2, 1, NONE);
	board2.scell(4, 1, NONE);
	board2.scell(6, 1, NONE);
	board2.scell(1, 6, NONE);
	board2.scell(3, 6, NONE);
	board2.scell(5, 6, NONE);
	board2.scell(7, 6, NONE);
	std::cout << board2 << std::endl;
	board2.start_move(PWHITE);
	
	EXPERIMENT exp2(board2, 10, 30, 0.10, 2, 10);
	exp2.run(AI_PRL,  "parallel ai (2 threads)");
	exp2.run(AI_PRL2, "parallel ai (4 threads)");
	exp2.run(AI_SEQ,  "sequence ai (1 thread )");
	
	return 0;
}


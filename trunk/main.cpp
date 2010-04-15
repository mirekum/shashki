#include "experiment.h"

// entry point
int main () {
	BOARD board;
	std::cout << board << std::endl;
	board.start_move(PWHITE);
	
	EXPERIMENT exp(board, 10, 30, 0.10, 2, 8);
	exp.run(AI_PRL,  "parallel ai (2 threads)");
	exp.run(AI_PRL2, "parallel ai (4 threads)");
	exp.run(AI_SEQ,  "sequence ai (1 thread )");
	
	return 0;
}


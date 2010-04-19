#include "experiment.h"

// entry point
int main () {
	BOARD board;
	std::cout << board << std::endl;
	
	EXPERIMENT exp(board, PWHITE, 50, 1000, 0.10, 5, 7);
	exp.run(AI_PRL); // 2 threads
	exp.run(AI_SEQ); // sequence
	exp.run(AI_PRL2); // 4 threads
	
	return 0;
}


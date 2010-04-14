#include "game.h"
#include "tournament.h"
#include "experiment.h"

// entry point
int main () {
	TOURNAMENT t;
	
	//t.play(AI_SEQ, 5, AI_SEQ, 5);
	//t.play(AI_SEQ, 5, AI_PRL, 5);
	//t.play(AI_PRL, 5, AI_PRL, 5);
	
	t.tournament(AI_SEQ, 6, AI_SEQ, 4, 1);
	t.tournament(AI_SEQ, 6, AI_PRL, 4, 1);
	t.tournament(AI_PRL, 6, AI_PRL, 4, 1);
	
	EXPERIMENT p;
	BOARD board;
	// set initial figures position on the board
	//p.start(board, AI_PRL, 8);
	//p.start(board, AI_SEQ, 8);
	
	return 0;
}


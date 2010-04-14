#include "game.h"
#include "tournament.h"

// entry point
int main () {
	// GAME(white player, black player)
	//GAME draughts(AI_SEQ, AI_PRL);
	
	TOURNAMENT t;
	
	//t.play(AI_SEQ, 5, AI_SEQ, 5);
	//t.play(AI_SEQ, 5, AI_PRL, 5);
	//t.play(AI_PRL, 5, AI_PRL, 5);
	
	t.tournament(AI_SEQ, 3, AI_SEQ, 3, 10);
	t.tournament(AI_SEQ, 3, AI_PRL, 3, 10);
	t.tournament(AI_PRL, 3, AI_PRL, 3, 10);
	
	return 0;
}


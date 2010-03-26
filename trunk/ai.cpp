#include <iostream>
#include "board.h"
#include "ai.h"

/* methods of class of the ai player */

// chooses partial half-move
MOVE AI_PLAYER::get_move(BOARD board) {
	// partial half-move
	MOVE res;
	// choose the best partial half-move
	choose(board, type, &res);
	// result
	return res;
}

// choose the best partial half-move
int AI_PLAYER::choose(BOARD board, PCOLOR _type, MOVE *res, int step, int last, bool smflag) {
	// not last partial half-move
	if (step < max_step) {
		bool minimax = (step % 2 == 0 ? 1 : 0); // max or min we must calculate (1 - max, 0 - min)
		int max = -MINMAX_END, min = MINMAX_END; // max and min of SRF value
		// go round all figures on the board
		for (int i = 0; i < board.size; i++) {
			for (int j = 0; j < board.size; j++) {
				int m;
				CELL d(i, j), arr[16];
				// first partial half-move
				if (smflag) board.start_move(_type);
				// array of the possible partial half-moves for current figure
				m = board.moves(d, arr);
				// for debugging
				if (step < 0) {
					for (int k = 0; k < m; k++) {
						std::cout << d.x << ", " << d.y << " -> " << arr[k].x << ", " << arr[k].y << std::endl;
					}
				}
				// go round array of the possible partial half-moves for current figure
				for (int k = 0; k < m; k++) {
					int s; // current SRF value
					BOARD board_copy = board;
					// first partial half-move
					if (smflag) board.start_move(_type);
					// exec current partial half-move
					board_copy.move(d, arr[k]);
					// half-move continuing
					if (board_copy.moves(arr[k])) {
						// continue current half-move
						s = choose(board_copy, _type, NULL, step, (minimax ? max : min), false);
					}
					// half-move is finished
					else {
						// start enemy half-move
						s = choose(board_copy, _type == PWHITE ? PBLACK : PWHITE, NULL, step + 1, (minimax ? max : min), true);
					}
					// calculate max of SRF values
					if (minimax) {
						if (s >= max) {
							if (res != NULL) {
								res->from = d;
								res->to = arr[k];
							}
							max = s;
						}
						// alpha-beta pruning
						if (ab && s > last && last > -MINMAX_END && last < MINMAX_END) {
							return s;
						}
					}
					// calculate min of SRF values
					else {
						if (s <= min) {
							if (res != NULL) {
								res->from = d;
								res->to = arr[k];
							}
							min = s;
						}
						// alpha-beta pruning
						if (ab && s < last && last > -MINMAX_END && last < MINMAX_END) {
							return s;
						}
					}
				}
				
			}
		}
		// result of going round this tree branch
		return (minimax ? max : min);
	}
	// last partial half-move
	else {
		return srf(board);
	}
	// error
	return 0;
}

// statictiс rating function
int AI_PLAYER::srf(BOARD board) {
	// for white player
	if (type == PWHITE) {
		return (board.white() - board.white_king() - board.black() + board.black_king()) + 3*(board.white_king() - board.black_king());
	}
	// for black player
	else if (type == PBLACK) {
		return (board.black() - board.black_king() - board.white() + board.white_king()) + 3*(board.black_king() - board.white_king());
	}
	// error
	return 0;
}


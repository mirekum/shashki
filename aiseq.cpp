#include <iostream>
#include "board.h"
#include "aiseq.h"

/* methods of class of the ai player */

// choose partial half-move
MOVE AI_SEQ_PLAYER::get_move(BOARD board) {
	MOVE res;
	choose(board, type, &res); // choose the best partial half-move
	
	//std::cout << "result: " << res.from.x << ", " << res.from.y << " -> " << res.to.x << ", " << res.to.y << std::endl;
	
	return res;
}

// choose the best partial half-move
int AI_SEQ_PLAYER::choose(BOARD board, PCOLOR _type, MOVE *res, int step, int last, bool smflag) {
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
				// go round array of the possible partial half-moves for current figure
				for (int k = 0; k < m; k++) {
					int s; // current SRF value
					BOARD board_copy = board;
					// exec current partial half-move
					board_copy.move(d, arr[k]);
					// for debugging
					if (step < 0) {
						for (int q = 0; q < step; q++) {
							std::cout << "  ";
						}
						std::cout << d.x << ", " << d.y << " -> " << arr[k].x << ", " << arr[k].y << std::endl;
					}
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
							//if (step <= 2) std::cout << "================ ab1 pruning detected! ================\n"; // for debugging
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
							//if (step <= 1) std::cout << "================ ab2 pruning detected! ================\n"; // for debugging
							return s;
						}
					}
					// for debugging
					if (step < 0) {
						std::cout << "> [" << s << "] " <<
							"(" << d.x << ", " << d.y << ") -> (" << arr[k].x << ", " << arr[k].y << ")" << std::endl;
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
	
	return 0;
}

// statictiс rating function
int AI_SEQ_PLAYER::srf(BOARD board) {
	if (type == PWHITE) {
		return (board.white() - board.black()) + 2*(board.white_king() - board.black_king());
	}
	else if (type == PBLACK) {
		return (board.black() - board.white()) + 2*(board.black_king() - board.white_king());
	}
	
	return 0;
}


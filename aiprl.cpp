#include <iostream>
#include <pthread.h>
#include "board.h"
#include "aiprl.h"

/* methods of class of the parallel ai player */

// chooses partial half-move
MOVE AI_PRL_PLAYER::get_move(BOARD board) {
	MOVE res; // the best move
	CHOOSEN_MOVE_ARRAY moves_queue; // first level moves queue
	pthread_t thread1, thread2; // child threads
	int iret1, iret2; // threads ids
	// go round all figures on the board and make moves queue
	for (int i = 0; i < board.size; i++) {
		for (int j = 0; j < board.size; j++) {
			CELL current_from(i, j), current_moves[16];
			int current_moves_count = board.moves(current_from, current_moves);
			for (int k = 0; k < current_moves_count; k++) {
				CHOOSEN_MOVE current_move(current_from, current_moves[k]);
				moves_queue.push_back(current_move);
			}
		}
	}
	
	// threads synchronisation object
	MOVES_SYNC sync_obj, *sync = &sync_obj;
	pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
	sync->plr = this;
	sync->board = &board;
	sync->moves_queue = &moves_queue;
	sync->queue_mutex = &queue_mutex;
	sync->next_move_num = 0;
	
	// run two child threads
	iret1 = pthread_create(&thread1, NULL, &ai_prl_first_choose, (void*)sync);
	if (iret1) exit(1);
	iret2 = pthread_create(&thread2, NULL, &ai_prl_first_choose, (void*)sync);
	if (iret2) exit(1);
	
	// wait threads termination
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	
	// calculate maximum of moves marks and choose the best move
	int max = -MINMAX_END;
	for (int i = 0; i < moves_queue.size(); i++) {
		std::cout << "move #" << i << ": " << moves_queue[i].mark << std::endl;
		if (moves_queue[i].mark >= max) {
			max = moves_queue[i].mark;
			res.from = moves_queue[i].from;
			res.to = moves_queue[i].to;
		}
	}
	
	std::cout << "result: " << res.from.x << ", " << res.from.y << " -> " << res.to.x << ", " << res.to.y << " [" << max << "]" << std::endl;
	
	// return the best move
	return res;
}

void *ai_prl_first_choose(void *ptr) {
	// threads synchronisation object
	MOVES_SYNC *sync = (MOVES_SYNC*)ptr;
	
	// while there are legacy moves in queue
	bool moves_exist = true;
	while (moves_exist) {
		CHOOSEN_MOVE *move = 0;
		// get move from queue
		pthread_mutex_lock(sync->queue_mutex);
		if (sync->next_move_num != sync->moves_queue->size()) {
			move = &((*(sync->moves_queue))[sync->next_move_num]);
			std::cout << "get move from queue #" << sync->next_move_num << ": "
					  << move->from.x << ", " << move->from.y << " -> " << move->to.x << ", " << move->to.y << std::endl;
			++sync->next_move_num;
		} else {
			moves_exist = false;
		}
		pthread_mutex_unlock(sync->queue_mutex);
		
		// calculate mark for gotten move
		if (move) {
			BOARD board_copy = *(sync->board);
			MOVE res;
			board_copy.start_move(sync->plr->type);
			board_copy.move(move->from, move->to);
			// half-move continuing
			if (board_copy.moves(move->to)) {
				// continue current half-move
				move->mark = sync->plr->choose(board_copy, sync->plr->type, &res, 0, -sync->plr->MINMAX_END, false);
			}
			// half-move is finished
			else {
				// start enemy half-move
				move->mark = sync->plr->choose(board_copy, sync->plr->type == PWHITE ? PBLACK : PWHITE, &res, 1, -sync->plr->MINMAX_END, true);
			}
			
		}
	}
}

// choose the best partial half-move
int AI_PRL_PLAYER::choose(BOARD board, PCOLOR _type, MOVE *res, int step, int last, bool smflag) {
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
					// first partial half-move
					if (smflag) board.start_move(_type);
					// exec current partial half-move
					board_copy.move(d, arr[k]);
					// for debugging
					if (step <= 0) {
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
						if (s > last && last > -MINMAX_END && last < MINMAX_END) {
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
						if (s < last && last > -MINMAX_END && last < MINMAX_END) {
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
int AI_PRL_PLAYER::srf(BOARD board) {
	if (type == PWHITE) {
		return (board.white() - board.black()) + 2*(board.white_king() - board.black_king());
	}
	else if (type == PBLACK) {
		return (board.black() - board.white()) + 2*(board.black_king() - board.white_king());
	}
	
	return 0;
}


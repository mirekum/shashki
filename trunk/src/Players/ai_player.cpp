#include "Players/ai_player.h"

// choose partial half-move
void Ai_Player::execMove(BOARD board) {
	CHOOSEN_MOVE_ARRAY moves_queue; // first level moves queue
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
	pthread_mutex_t mark_mutex = PTHREAD_MUTEX_INITIALIZER;
	sync->plr = this;
	sync->board = &board;
	sync->next_move_num = 0;
	sync->moves_queue = &moves_queue;
	sync->queue_mutex = &queue_mutex;
	sync->alpha = -MINMAX_END;
	sync->beta = MINMAX_END;
	sync->mark_mutex = &mark_mutex;
	
	// child threads
	std::vector<pthread_t> threads(thr_num);
	
	// run child threads
	for (int i = 0; i < thr_num; i++) {
		if (pthread_create(&threads[i], NULL, &ai_prl_first_choose, (void*)sync)) exit(1);
	}
	
	// wait threads termination
	for (int i = 0; i < thr_num; i++) {
		pthread_join(threads[i], NULL);
	}
	
	// choose the best move
	int score = -MINMAX_END, rnd = 0;
	std::vector<CHOOSEN_MOVE> best_moves;
	//qDebug() << "--------------------------- " << thr_num << " ------";
	for (int i = 0; i < moves_queue.size(); i++) {
		//qDebug() << i+1 << ") " << moves_queue[i].from.x+1 << "," << moves_queue[i].from.y+1 << " -> "
		//		 << moves_queue[i].to.x+1 << "," << moves_queue[i].to.y+1 << " || " << moves_queue[i].mark;
		if (moves_queue[i].mark >= score) {
			score = moves_queue[i].mark;
		}
	}
	//qDebug() << "best score: " << score;
	for (int i = 0; i < moves_queue.size(); i++) {
		if (moves_queue[i].mark == score) {
			best_moves.push_back(moves_queue[i]);
		}
	}
	rnd = rand() % best_moves.size();
	rnd = best_moves.size()-1;
	result.from = best_moves[rnd].from;
	result.to = best_moves[rnd].to;
	//qDebug() << "result [" << rnd+1 << "/" << best_moves.size() << "]: " << result.from.x+1 << "," << result.from.y+1 << " -> "
	//					<< result.to.x+1 << "," << result.to.y+1 << " || " << score;
	
	// return the best move
	//getchar();
	//sleep(1);
	emit moveExecuted();
}

// first call of choose functio
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
			++sync->next_move_num;
		} else {
			moves_exist = false;
		}
		pthread_mutex_unlock(sync->queue_mutex);
		
		// calculate mark for gotten move
		if (move) {
			BOARD board_copy = *(sync->board);
			board_copy.startMove(sync->plr->color);
			board_copy.move(move->from, move->to);
			
			// half-move continuing
			if (board_copy.moves(move->to)) {
				// continue current half-move
				move->mark = sync->plr->choose(board_copy, sync->plr->color, 0, sync->alpha, sync->beta, false);
			}
			// half-move is finished
			else {
				// start enemy half-move
				move->mark = -sync->plr->choose(board_copy, sync->plr->color == WHITE ? BLACK : WHITE, 1, -sync->beta, -sync->alpha, true);
			}
			
			// remember mark
			/*{
				pthread_mutex_lock(sync->mark_mutex);
				if (move->mark > sync->alpha) {
					sync->alpha = move->mark;
				}
				if (move->mark < sync->beta) {
					sync->beta = move->mark;
				}
				pthread_mutex_unlock(sync->mark_mutex);
			}*/
		}
	}
}

// choose the best partial half-move
int Ai_Player::choose(BOARD board, COLOR cColor, int step, int alpha, int beta, bool smflag) {
	// not last partial half-move
	if (step < max_step) {
		int score = -MINMAX_END;
		// go round all figures on the board
		for (int i = 0; i < board.size; i++) {
			for (int j = 0; j < board.size; j++) {
				int m;
				CELL d(i, j), arr[16];
				// first partial half-move
				if (smflag) board.startMove(cColor);
				// array of the possible partial half-moves for current figure
				m = board.moves(d, arr);
				// go round array of the possible partial half-moves for current figure
				for (int k = 0; k < m; k++) {
					int s; // current SRF value
					BOARD board_copy = board;
					// exec current partial half-move
					board_copy.move(d, arr[k]);
					// half-move continuing
					if (board_copy.moves(arr[k])) {
						// continue current half-move
						s = choose(board_copy, cColor, step, alpha, beta, false);
					}
					// half-move is finished
					else {
						// start enemy half-move
						s = -choose(board_copy, cColor == WHITE ? BLACK : WHITE, step + 1, -beta, -alpha, true);
					}
					// calculate max of SRF value
					if (s > score) score = s;
					if (score > alpha) alpha = score;
					if (alpha >= beta)return alpha;
				}
			}
		}
		// result of going round this tree branch
		return score;
	}
	// last partial half-move
	else {
		return srf(board);
	}
	
	return 0;
}

// statistiс rating function
int Ai_Player::srf(BOARD board) {
	if (color == WHITE) {
		return (board.white() - board.black()) + 2*(board.whiteKing() - board.blackKing());
	}
	else if (color == BLACK) {
		return (board.black() - board.white()) + 2*(board.blackKing() - board.whiteKing());
	}
	
	return 0;
}


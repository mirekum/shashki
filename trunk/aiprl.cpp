#include <iostream>
#include <pthread.h>
#include "board.h"
#include "aiprl.h"

/* methods of class of the parallel ai player */

// choose partial half-move
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
	pthread_mutex_t mark_mutex = PTHREAD_MUTEX_INITIALIZER;
	sync->plr = this;
	sync->board = &board;
	sync->next_move_num = 0;
	sync->moves_queue = &moves_queue;
	sync->queue_mutex = &queue_mutex;
	sync->mark = -MINMAX_END;
	sync->mark_mutex = &mark_mutex;
	
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
		//std::cout << "move #" << i << ": " << moves_queue[i].mark << std::endl;
		if (moves_queue[i].mark >= max) {
			max = moves_queue[i].mark;
			res.from = moves_queue[i].from;
			res.to = moves_queue[i].to;
		}
	}
	
	//std::cout << "result: " << res.from.x << ", " << res.from.y << " -> " << res.to.x << ", " << res.to.y << " [" << max << "]" << std::endl;
	
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
			//std::cout << "get move from queue #" << sync->next_move_num << ": "
			//		  << move->from.x << ", " << move->from.y << " -> " << move->to.x << ", " << move->to.y << std::endl;
			++sync->next_move_num;
		} else {
			moves_exist = false;
		}
		pthread_mutex_unlock(sync->queue_mutex);
		
		// calculate mark for gotten move
		if (move) {
			BOARD board_copy = *(sync->board);
			//MOVE res;
			board_copy.start_move(sync->plr->type);
			board_copy.move(move->from, move->to);
			// half-move continuing
			if (board_copy.moves(move->to)) {
				// continue current half-move
				move->mark = sync->plr->choose(board_copy, sync->plr->type, NULL, 0, sync->mark, false);
			}
			// half-move is finished
			else {
				// start enemy half-move
				move->mark = sync->plr->choose(board_copy, sync->plr->type == PWHITE ? PBLACK : PWHITE, NULL, 1, sync->mark, true);
			}
			// remember mark
			pthread_mutex_lock(sync->mark_mutex);
			if (move->mark > sync->mark) {
				sync->mark = move->mark;
			}
			pthread_mutex_unlock(sync->mark_mutex);
			
		}
	}
}


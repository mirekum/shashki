#ifndef _VIEW_BOARD_H_
	#define _VIEW_BOARD_H_
	
	#include "View/view.h"
	#include "Players/player.h"
	
	class View_Board: public View, public Player {
		Q_OBJECT
	public:
		View_Board() {}
		// get player type
		virtual PLAYER_TYPE type() {return HUMAN;};
	public slots:
		// get move from human
		virtual MOVE getMove(BOARD board);
	};
	
#endif


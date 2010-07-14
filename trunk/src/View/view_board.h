#ifndef _VIEW_BOARD_H_
	#define _VIEW_BOARD_H_
	
	#include "View/view.h"
	#include "View/view_main.h"
	#include "Players/player.h"
	
	class View_Board: public View, public Player {
		Q_OBJECT
	protected:
		QWidget *window;
	public:
		View_Board(View_Main &main_ui);
		// get player type
		virtual PLAYER_TYPE type() {return HUMAN;};
	public slots:
		// get move from human
		virtual MOVE getMove(BOARD board);
	};
	
#endif


#ifndef _VIEW_FINISHGAME_H_
	#define _VIEW_FINISHGAME_H_
	
	#include "View/view.h"
	#include "View/view_main.h"
	#include "Model/game.h"
	
	class View_FinishGame: public QObject, public View {
		Q_OBJECT
	protected:
		QWidget *window;
		QLabel *box;
	public:
		View_FinishGame(View_Main &main_ui);
		void show(GAMESTATE res_flag);
	};
	
#endif


#ifndef _VIEW_STARTGAME_H_
	#define _VIEW_STARTGAME_H_
	
	#include "View/view.h"
	#include "View/view_main.h"
	
	class View_StartGame: public View {
		Q_OBJECT
	protected:
		View_Main *main_ui;
		QWidget *window;
	public:
		View_StartGame(View_Main &_main_ui);
		// show first screen
		void show();
	};
	
#endif


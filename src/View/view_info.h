#ifndef _VIEW_INFO_H_
	#define _VIEW_INFO_H_
	
	#include "Model/game.h"
	#include "View/view.h"
	#include "View/view_main.h"
	
	class View_Info: public QObject, public View {
		Q_OBJECT
	protected:
		Game *game;
		QWidget *window;
		QLabel *label_history;
		QListWidget *list_history_widget;
	public:
		View_Info(View_Main &main_ui);
		// view initialization
		void init(Game *_game);
		// view hiding
		void hide();
	protected slots:
		void updateHistory();
		void rollHistory(QListWidgetItem * state);

	};
	
#endif


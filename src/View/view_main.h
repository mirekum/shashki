#ifndef _VIEW_MAIN_H_
	#define _VIEW_MAIN_H_
	
	#include "View/view.h"
	
	class View_Main: public QObject, public View {
		Q_OBJECT
	protected:
		QMainWindow *window;
	public:
		View_Main();
		~View_Main();
		// show main app window
		void show();
		// getters
		QWidget* getWindow() {return window;};
	protected slots:
		void menuNewgame();
		void menuExit();
	};
	
#endif


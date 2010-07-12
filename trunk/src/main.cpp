#include "View/view_cui.h"
#include "View/view_gui.h"

// entry point
int main (int argc, char** argv) {
	VIEW_GUI view(argc, argv);
	return view.exec();
}


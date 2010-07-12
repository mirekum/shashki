#ifndef _VIEW_INPUT_H_
	#define _VIEW_INPUT_H_
	
	// view input data class
	class VIEW_INPUT {
	public:
		// get move from human player
		virtual MOVE humanGetmove(BOARD board) = 0;
	};
	
#endif


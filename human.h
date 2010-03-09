#ifndef _HUMAN_H_
	#define _HUMAN_H_
	
	// ввод C-подобной строки
	void fgetstr (char *str, int len);
	
	// класс "Игрок-человек"
	class HUMAN_PLAYER: public PLAYER {
	public:
		// выполнение хода
		virtual BOARD_MOVE move(BOARD board);
	};
	
#endif


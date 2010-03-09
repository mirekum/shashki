#ifndef _PLAYER_H_
	#define _PLAYER_H_
	
	#define HUMAN 10
	#define AI    20
	#define AI2   30
		
	// класс "Игрок в шашки"
	class PLAYER {
	protected:
		// цвет игрока
		int type;
	public:
		// конструктор класса
		PLAYER () {type = 0;}
		// установка цвета игрока
		void setType(int _type) {type = _type;};
		// выполнение неполного полухода
		virtual BOARD_MOVE move(BOARD board) = 0;
	};
	
#endif


#ifndef _BOARD_H_
	#define _BOARD_H_
	
	#define WHITE      +1 // белая шашка
	#define WHITE_KING +2 // белая дамка
	#define BLACK      -1 // чёрная шашка
	#define BLACK_KING -2 // чёрная дамка
	
	#define CANMOVE_NO    0 // нельзя ходить
	#define CANMOVE_YES   1 // можно ходить, это обычный неполный полуход
	#define CANMOVE_EAT_W 2 // можно ходить, это неполный полуход - поедание белой шашки
	#define CANMOVE_EAT_B 3 // можно ходить, это неполный полуход - поедание чёрной шашки
	
	#define ISWIN_WHITE 1 // выиграли белые
	#define ISWIN_BLACK 2 // выиграли чёрные
	#define ISWIN_DRAW  3 // ничья
	#define ISWIN_GAME  0 // игра не закончилась
	
	// класс, описывающий клетку доски
	class BOARD_CELL {
	public:
		int x, y;
		// конструкторы класса
		BOARD_CELL(): x(0), y(0) {};
		BOARD_CELL(int _x, int _y): x(_x), y(_y) {};
	};
	
	// класс, описывающий ход с одной клетки на другую
	class BOARD_MOVE {
	public:
		BOARD_CELL from, to;
		// конструкторы класса
		BOARD_MOVE() {};
		BOARD_MOVE(BOARD_CELL _from, BOARD_CELL _to) {from = _from; to = _to;};
	};
		
	// класс "Доска для игры в шашки"
	class BOARD {
	protected:
		// размер доски и начальное кол-во шашек
		const static int size = 8;
		// кол-во белых и чёрных
		int b, w;
		// массив клеток доски; 0 - пусто, >0 - белые, <0 - чёрные
		char cells[size][size]; // [x][y]; x - столбец, y - строка
		// флаг, указывающий на первый неполный полуход
		bool ufirst;
		// флаг, указывающий на факт съедения в прошлом неполном полуходе
		bool ueaten;
		// цвет игрока на текущий полуход
		int utype;
		// заблокированная на текущий полуход шашка
		BOARD_CELL ublocked;
	public:
		// конструктор класса
		explicit BOARD();
		// начало полухода
		void start_move(int _type);
		// выполнение неполного полухода
		int move(BOARD_MOVE _move);
		int move(BOARD_CELL /* from */ a, BOARD_CELL /* to */ z);
		int move(int x1, int y1, int x2, int y2);
		// возможность неполного полухода
		int can_move(BOARD_MOVE move, int _type = 0);
		int can_move(BOARD_CELL /* from */ a, BOARD_CELL /* to */ z, int _type = 0);
		int can_move(int x1, int y1, int x2, int y2, int _type = 0);
		// возможность продолжения хода
		int can_move(int _type);
		// получение набора возможных неполных полуходов для заданной точки
		int moves(BOARD_CELL cell, BOARD_CELL *arr = NULL);
		// проверка конца игры (одна из сторон выиграла)
		int is_win();
		// вывод доски на экран
		friend std::ostream& operator<< (std::ostream &cout, BOARD &board);
		// размер доски
		int getSize() {return size;}
		// флаг, указывающий на первый неполный полуход
		int first() {return ufirst;}
		// количество белых
		int white() {return w;}
		// количество чёрных
		int black() {return b;}
		
	};
	
#endif

#ifndef _Board_h
#define _Board_h

#include "Point.h"
#include"Common.h"
class Board
{
private:
	int size;
	int	left, top;
	Point** pArr;
public:
	Board(int, int, int);
	void setBoard(int a[15][15]);
	~Board();
	int getSize();
	int getXAt(int, int);
	int getYAt(int, int);
	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool);
	int checkWin(int, int);
	int testBoard(int, int);
	bool isMatch(int a[]);
	COORD getCOORD(int, int);
	int getCheck(int, int);
	void setCheckAt(int, int, int);
	
};

#endif

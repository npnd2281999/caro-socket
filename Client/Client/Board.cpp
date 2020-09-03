#include "Board.h"

Board::Board(int pSize, int pX, int pY)
{
	size = pSize;
	left = pX;
	top = pY;
	pArr = new Point*[pSize];
	for (int i = 0; i < pSize; i++)
	{
		pArr[i] = new Point[pSize];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pArr[i][j].setX(4 * j + left + 2);
			pArr[i][j].setY(2 * i + top + 1);
			pArr[i][j].setCheck(0);
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < size; i++)
	{
		delete[] pArr[i];
	}
	delete[] pArr;
	pArr = NULL;
}

int Board::getSize()
{
	return size;
}

int Board::getXAt(int i, int j)
{
	return pArr[i][j].getX();
}

int Board::getYAt(int i, int j)
{
	return pArr[i][j].getY();
}

void Board::resetData()
{
	if (size == 0)
		return;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pArr[i][j].setX(4 * j + left + 2);
			pArr[i][j].setY(2 * i + top + 1);
			pArr[i][j].setCheck(0);
		}
	}
}

void Board::drawBoard()
{
	if (pArr == NULL)
		return;
	for (int i = 0; i <= size; i++)
	{
		for (int j = 0; j <= size; j++)
		{
			Common::setTextColor(240);
			Common::gotoXY(left + 4 * i, top + 2 * j);
			cout << ".";
			if (i < size && j < size)
			{
				if (pArr[i][j].getCheck() == -1) {
					Common::setTextColor(244);
					Common::gotoXY(pArr[i][j].getX(), pArr[i][j].getY());
					cout << "X";
				}
				else if (pArr[i][j].getCheck() == 1) {
					Common::setTextColor(243);
					Common::gotoXY(pArr[i][j].getX(), pArr[i][j].getY());
					cout << "O";
				}
			}
		}
	}
	Common::gotoXY(pArr[0][0].getX(), pArr[0][0].getY());
}

int Board::checkBoard(int pX, int pY, bool pTurn)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pArr[i][j].getX() == pX && pArr[i][j].getY() == pY && pArr[i][j].getCheck() == 0)
			{
				if (pTurn) pArr[i][j].setCheck(-1);
				else pArr[i][j].setCheck(1);
				return pArr[i][j].getCheck();
			}
		}
	}
	return 0;
}

int Board::testBoard(int pX, int pY)
{
	bool flag = 1;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pArr[i][j].getCheck() == 0) {
				flag = 0; break;
			}
		}
		//if (flag == 0) break;
	}
	if (flag == 1) return 0;
	else {
		return checkWin(pX, pY);
	}
}

COORD Board::getCOORD(int pX, int pY)
{
	COORD c;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (pArr[i][j].getX() == pX && pArr[i][j].getY() == pY)
			{
				c.X = i;
				c.Y = j;
				return c;
			}
		}
	}
}

int Board::checkWin(int pX, int pY)
{
	COORD c = getCOORD(pX, pY);
	int pWin = pArr[c.X][c.Y].getCheck();
	int isWinner = 2;
	//Kiểm tra cột
	/*************************/
	int testArr1[9] = { 0,0,0,0,1,0,0,0,0 };
	for (int i = 1; i <= 4; i++)
	{
		if (c.X - i >= 0)
		{
			if (pArr[c.X - i][c.Y].getCheck() == pWin)
			{
				testArr1[4 - i] = 1;
			}
		}
		if (c.X + i < size)
		{
			if (pArr[c.X + i][c.Y].getCheck() == pWin)
			{
				testArr1[4 + i] = 1;
			}
		}
	}
	if (isMatch(testArr1)) return pWin;
	// Kiểm tra hàng
	/************************/
	int testArr2[9] = { 0,0,0,0,1,0,0,0,0 };
	for (int i = 1; i <= 4; i++)
	{
		if (c.Y - i >= 0)
		{
			if (pArr[c.X][c.Y - i].getCheck() == pWin)
			{
				testArr2[4 - i] = 1;
			}
		}
		if (c.Y + i < size)
		{
			if (pArr[c.X][c.Y + i].getCheck() == pWin)
			{
				testArr2[4 + i] = 1;
			}
		}
	}

	if (isMatch(testArr2)) return pWin;

	// Chéo chính

	int testArr3[9] = { 0,0,0,0,1,0,0,0,0 };

	for (int i = 1; i <= 4; i++)
	{
		if (c.X - i >= 0 && c.Y - i >= 0)
		{
			if (pArr[c.X - i][c.Y - i].getCheck() == pWin)
			{
				testArr3[4 - i] = 1;
			}
		}
		if (c.X + i < size && c.Y + i < size)
		{
			if (pArr[c.X + i][c.Y + i].getCheck() == pWin)
			{
				testArr3[4 + i] = 1;
			}
		}
	}

	if (isMatch(testArr3)) return pWin;

	// chéo phụ
	int testArr4[9] = { 0,0,0,0,1,0,0,0,0 };
	for (int i = 1; i <= 4; i++)
	{
		if (c.X - i >= 0 && c.Y + i < size)
		{
			if (pArr[c.X - i][c.Y + i].getCheck() == pWin)
			{
				testArr4[4 - i] = 1;
			}
		}
		if (c.X + i < size && c.Y - i >= 0)
		{
			if (pArr[c.X + i][c.Y - i].getCheck() == pWin)
			{
				testArr4[4 + i] = 1;
			}
		}
	}

	if (isMatch(testArr4)) return pWin;

	return 2;
}

bool Board::isMatch(int a[])
{
	int dem = 0;
	for (int i = 0; i < 9; i++)
	{
		if (a[i] == 1)
		{
			dem++;
		}
		else
		{
			if (dem >= 5)
				return true;
			else
				dem = 0;
		}
	}
	if (dem >= 5) return true;
	else return false;
}

int Board::getCheck(int i, int j)
{
	return pArr[i][j].getCheck();
}

void Board::setCheckAt(int n, int m, int k)
{
	pArr[n][m].setCheck(k);
}



void Board::setBoard(int a[15][15])
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			pArr[i][j].setCheck(a[i][j]);
		}
	}
}


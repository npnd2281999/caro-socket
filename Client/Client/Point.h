#ifndef _Point_h
#define _Point_h

#include "Common.h"

class Point
{
private:
	int x, y, check;
public:
	Point();
	Point(int, int);
	bool setCheck(int);
	int getX();
	int getY();
	int getCheck();
	void setX(int);
	void setY(int);
};

#endif


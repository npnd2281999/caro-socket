#include "Point.h"

Point::Point()
{
	x = y = check = 0;
}

Point::Point(int pX, int pY)
{
	x = pX;
	y = pY;
	check = 0;
}

int Point::getX()
{
	return x;
}

int Point::getY()
{
	return y;
}

bool Point::setCheck(int pCheck)
{
	if (pCheck == -1 || pCheck == 1 || pCheck == 0)
		check = pCheck;
	return true;
}

int Point::getCheck()
{
	return check;
}

void Point::setX(int pX)
{
	x = pX;
}

void Point::setY(int pY)
{
	y = pY;
}
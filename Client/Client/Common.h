#ifndef _Common_h
#define _Common_h

#include <iostream>
#include <Windows.h>
#include<fstream>
#include<string>
#include<io.h>

using namespace std;

class Common
{
public:
	static void fixConsoleWindow();
	static void gotoXY(int, int);
	static void hideCursor(bool);
	static void removeScrollbar();
	static void setSize();
	static void Result(string);
	static void gameName(int);
	static void setTextColor(int);
};

#endif

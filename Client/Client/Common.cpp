#include "Common.h"

void Common::fixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void Common::gotoXY(int X, int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Common::hideCursor(bool X)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  ConCurInf;
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = X;
	SetConsoleCursorInfo(handle, &ConCurInf);
}

void Common::removeScrollbar()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(handle, &info);
	COORD new_size =
	{
		info.srWindow.Right - info.srWindow.Left + 1,
		info.srWindow.Bottom - info.srWindow.Top + 1
	};
	SetConsoleScreenBufferSize(handle, new_size);
}

void Common::setSize()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, 115 * 10, 70 * 10, TRUE);
}

void Common::Result(string filename)
{
	system("cls");
	fstream f;
	string s;
	f.open(filename, ios::in);
	Common::setTextColor(243);
	int i = 10;
	while (!f.eof())
	{
		getline(f, s);
		Common::gotoXY(40, i++);
		cout << s << endl;
	}
	Common::gotoXY(40, i);
}

void Common::gameName(int color)
{
	string s;
	fstream f;
	f.open("CARO1.txt", ios::in);
	int i = 2;
	Common::setTextColor(color);
	while (!f.eof())
	{
		getline(f, s);
		Common::gotoXY(26, i++);
		cout << s << endl;
	}
	Common::gotoXY(25, i);
	cout << "					Game will start in seconds..." << endl;
	Sleep(2000);
}

void Common::setTextColor(int color)
{
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleColor, color);
}

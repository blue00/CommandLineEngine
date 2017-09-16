#include "screen.h"
#include <iostream>

Screen::Screen()
{
	SetWindow(screenX , screenY);
	HideCursor();
	Clear();
	ForceDraw();
}

void Screen::SetString(int x, int y, std::string str)
{
	cursorMove(x, y);

	for (size_t i = 0; i < str.length(); i++)
	{
		Set(x, y, str[i]);
		++x;
	}
}

void Screen::SetString(float x, float y, std::string str)
{
	int x_int = static_cast<int>(x);
	int y_int = static_cast<int>(y);

	Screen::SetString(x_int, y_int, str);
}

void Screen::SetTitle(std::wstring text)
{
	SetConsoleTitle(text.c_str());
}

void Screen::Set(int x, int y, char zeichen)
{
	if (CheckBounds(x, y))
	{
		map[y][x] = zeichen;
	}
}

char Screen::Get(int x, int y)
{
	if (CheckBounds(x, y))
	{
		return map[y][x];
	}
	else
	{
		return -1;
	}
}

inline bool Screen::CheckBounds(int x, int y)
{
	return (y > -1 && y < screenY && x > -1 && x < screenX);
}

bool Screen::CheckBounds(float x, float y)
{
	return (y > -1 && y < (float)screenY && x > -1 && x < (float)screenX);
}

void Screen::Clear(char zeichen)
{
	for (int y = 0; y < screenY; y++)
	{
		for (int x = 0; x < screenX; x++)
		{
			map[y][x] = zeichen;
		}
	}
}

void Screen::ForceDraw()
{
	for (int y = 0; y < screenY; y++)
	{
		for (int x = 0; x < screenX; x++)
		{
			if (drawMap[y][x] != map[y][x])
			{
				drawMap[y][x] = map[y][x];
			}

			// draw even nothing has changed
			cursorMove(x, y);
			std::cout << drawMap[y][x];
		}
	}
}

void Screen::DrawAtIfChanged(int x, int y)
{
	if (drawMap[y][x] != map[y][x])
	{
		drawMap[y][x] = map[y][x];
		cursorMove(x, y);
		std::cout << drawMap[y][x];
	}
}

void Screen::Draw()
{
	// at first we draw every even line, then every odd line
	// this is more pleasant for the eye

	for (int y = 0; y < screenY; y += 2)
	{
		for (int x = 0; x < screenX; x++)
		{
			DrawAtIfChanged(x, y);
		}
	}

	for (int y = 1; y < screenY; y += 2)
	{
		for (int x = 0; x < screenX; x++)
		{
			DrawAtIfChanged(x, y);
		}
	}
}

/* Set the window Size and buffer */
void Screen::SetWindow(int width, int height)
{
	// prevent line break problem at the corners
	++width;
	++height;

	_COORD coord;
	coord.X = width;
	coord.Y = height;

	_SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = height - 1;
	Rect.Right = width - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      //  Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            //  Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            //  Set Window Size 
}

/* Moves the console cursor to the given coordinates */
void Screen::cursorMove(int x, int y)
{
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

/* Moves the console cursor to the given coordinates */
void Screen::cursorMove(COORD point)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

void Screen::HideCursor()
{
	HANDLE myconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CURSOR;
	CURSOR.dwSize = 1;
	CURSOR.bVisible = FALSE;
	SetConsoleCursorInfo(myconsole, &CURSOR);
}
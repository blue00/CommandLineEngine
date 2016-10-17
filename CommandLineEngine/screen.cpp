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

	for (int i = 0; i < str.length(); i++)
	{
		Set(x, y, str[i]);
		++x;
	}
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

//@TODO: move this in math
std::vector<Point> Screen::Raytrace(int x0, int y0, int x1, int y1)
{
	std::vector<Point> points;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x = x0;
	int y = y0;
	int n = 1 + dx + dy;
	int x_inc = (x1 > x0) ? 1 : -1;
	int y_inc = (y1 > y0) ? 1 : -1;
	int error = dx - dy;
	dx *= 2;
	dy *= 2;

	for (; n > 0; --n)
	{
		Point newPoint;
		newPoint.x = x;
		newPoint.y = y;
		points.push_back(newPoint);

		if (error > 0)
		{
			x += x_inc;
			error -= dy;
		}
		else
		{
			y += y_inc;
			error += dx;
		}
	}

	return points;
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
			if (drawMap[y][x] != map[y][x]) //hat sich etwas verändert?
			{
				//änderung übernehmen
				drawMap[y][x] = map[y][x];
			}

			//IMMER zeichnen
			cursorMove(x, y);
			std::cout << drawMap[y][x];
		}
	}
}

void Screen::Draw()
{
	for (int y = 0; y < screenY; y++)
	{
		for (int x = 0; x < screenX; x++)
		{
			if (drawMap[y][x] != map[y][x]) //hat sich etwas verändert?
			{
				//änderung übernehmen und konsolenfenster aktualisieren
				drawMap[y][x] = map[y][x];
				cursorMove(x, y);
				std::cout << drawMap[y][x];
			}
		}
	}
}

/* Setzt die Fenstergröße (Und den Buffer auf die selbe Größe wie das Fenster) */
void Screen::SetWindow(int width, int height)
{
	//prevent line break problem at the corners
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

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
}

/* Bewegt den Cursor in der Konsole zum angegebenen Punkt */
void Screen::cursorMove(int x, int y)
{
	COORD point;
	point.X = x;
	point.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}

/* Bewegt den Cursor in der Konsole zum angegebenen Punkt */
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
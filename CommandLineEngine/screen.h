#pragma once

#include <Windows.h>
#include <string>

class Screen
{
public:
	Screen();
	HWND consoleWindow = GetConsoleWindow();
	static const int screenX = 100;
	static const int screenY = 40;
	void Set(int x, int y, char zeichen);
	char Get(int x, int y);
	void SetString(int x, int y, std::string str);
	void SetString(float x, float y, std::string str);
	void Draw();
	void Clear(char zeichen = ' ');
	void SetTitle(std::wstring text);
	inline bool CheckBounds(int x, int y);
	bool CheckBounds(float x, float y);
private:
	char map[screenY][screenX];
	void ForceDraw();
	char drawMap[screenY][screenX];
	void SetWindow(int Width, int Height);
	void cursorMove(int x, int y);
	void cursorMove(COORD point);
	void HideCursor();
};
#include "input.h"

// #include "conio.h"
#include <Windows.h>

Input::Input()
{
	// @CHANGE: these keycodes could be loaded from a text file -> keyboard configuration (menu) would be possible
	// https:// msdn.microsoft.com/en-us/library/dd375731%28VS.85%29.aspx
	KeyCode[FUNC_W] = 0x57;
	KeyCode[FUNC_S] = 0x53;
	KeyCode[FUNC_A] = 0x41;
	KeyCode[FUNC_D] = 0x44;
	KeyCode[FUNC_ESC] = VK_ESCAPE;

	ResetKeys();
}

bool Input::IsKeyPressed(int func) // true if key is pressed (and not pressed the tick before)
{
	if (KeyArray[func] == KEY_PRESSED)
	{
		KeyArray[func] = KEY_DOWN;
		return true;
	}
	return false;
}

bool Input::IsKeyDown(int func) // true if key is held down for more than one tick
{
	return KeyArray[func] > KEY_RELEASED;
}

bool Input::IsKeyReleased(int func) // true if released in this tick
{
	return KeyArray[func] == KEY_RELEASED;
}

void Input::Tick()
{
	for (int i = 0; i < USEDFUNCKEYS; ++i)
	{
		if (KeyArray[i] == KEY_RELEASED)
		{
			KeyArray[i] = KEY_NULL;
		}

		KeyUpdated[i] = false;
	}
 
	/* old method which reads the keys from the command line. we keep it here for just reference. */
	// while (_kbhit()) // while there is new input (= keys pressed)
	// {
	// 	int key = _getch();
	// 	KeyDown(key);
	// }

	// there is no key event we could use for keydown or up. therefore we must check the status of every key manually.
	for (int i = 0; i < USEDFUNCKEYS; ++i)
	{
		if (GetAsyncKeyState(KeyCode[i])) //is this key pressed atm?
		{
			KeyDown(i);
		}
	}

	//if a key was pressed in the last tick but not updated in the current tick we know it is released now
	for (int i = 0; i < USEDFUNCKEYS; ++i)
	{
		if (!KeyUpdated[i] && KeyArray[i] > KEY_RELEASED)
		{
			KeyUp(i);
		}
	}
}

void Input::ResetKeys()
{
	// reset keyboard
	for (int i = 0; i < USEDFUNCKEYS; ++i)
	{
		KeyArray[i] = KEY_NULL;
	}
}

Mathf::PointF Input::MousePos(Screen screen)
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(screen.consoleWindow, &p);

	Mathf::PointF point;

	// the 12.0 and 3.35 are found through trial and error @DEBUG: is there a consistent method which works with all console settings? (font, fontsize, ...)
	point.x = p.x / (screen.screenX / 12.0f);
	point.y = p.y / (screen.screenY / 3.35f);

	return point;
}

void Input::KeyDown(int index)
{
	if (index > -1 && KeyArray[index] < KEY_PRESSED)
	{
		KeyArray[index] = KEY_PRESSED;
	}

	KeyUpdated[index] = true;
}

void Input::KeyUp(int index)
{
	KeyArray[index] = KEY_RELEASED;
}

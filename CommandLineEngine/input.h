#pragma once

#include "screen.h"
#include "mathf.h"

class Input
{
public:
	const static int USEDFUNCKEYS = 5;

	const int FUNC_W = 0;
	const int FUNC_S = 1;
	const int FUNC_A = 2;
	const int FUNC_D = 3;
	const int FUNC_ESC = 4;

	Input();
	void Tick();
	bool IsKeyPressed(int func); //true wenn taste heruntergedrückt wurde (es geht nicht um das unten halten)
	bool IsKeyDown(int func); //true wenn gepresst
	bool IsKeyReleased(int func); //true wenn released
	void ResetKeys();
	Mathf::PointF MousePos(Screen screen);

private:
	/* KEY STATES - DO NOT CHANGE THIS IF YOU ADD A NEW KEY !!! */
	const int KEY_NULL = 0;
	const int KEY_RELEASED = 1;
	const int KEY_PRESSED = 2;
	const int KEY_DOWN = 3;

	int KeyCode[USEDFUNCKEYS];
	int KeyArray[USEDFUNCKEYS];
	bool KeyUpdated[USEDFUNCKEYS];
	void KeyDown(int keycode);
	void KeyUp(int index);
};
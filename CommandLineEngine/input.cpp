#include "input.h"

//#include "conio.h"
#include <Windows.h>

Input::Input()
{
	//@CHANGE: diese daten könnten aus einem textfile geladen werden -> tastenkonfiguration veränderbar, z.b. über ein optionsmenü
	//https://msdn.microsoft.com/en-us/library/dd375731%28VS.85%29.aspx
	KeyCode[FUNC_W] = 0x57;
	KeyCode[FUNC_S] = 0x53;
	KeyCode[FUNC_A] = 0x41;
	KeyCode[FUNC_D] = 0x44;
	KeyCode[FUNC_ESC] = VK_ESCAPE;

	ResetKeys();
}

bool Input::IsKeyPressed(int func) //true wenn taste heruntergedrückt wurde (es geht nicht um das unten halten)
{
	if (KeyArray[func] == KEY_PRESSED)
	{
		KeyArray[func] = KEY_DOWN;
		return true;
	}
	return false;
}

bool Input::IsKeyDown(int func) //true wenn gepresst
{
	return KeyArray[func] > KEY_RELEASED;
}

bool Input::IsKeyReleased(int func) //true wenn released
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

	//es gibt kein event wenn eine taste gedrückt oder losgelassen wird
	//deshalb muss hier jede taste auf druck geprüft werden
		 
	/* alte methode die die tasten aus der konsole liest */
	//while (_kbhit()) //solange es tasten zum lesen gibt
	//{
	//	int key = _getch();
	//	KeyDown(key); //taste setzt automatisch KeyUpdated auf true
	//}

	//für jede taste prüfen ob diese gedrückt wird
	for (int i = 0; i < USEDFUNCKEYS; ++i)
	{
		if (GetAsyncKeyState(KeyCode[i]))
		{
			KeyDown(i);
		}
	}

	//alle tasten die nicht geupdated wurden aber einen gedrückten status haben sind losgelassen worden
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
	//reset keyboard
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

	//werte durch rummprobieren herausgefunden
	point.x = p.x / (screen.screenX / 12.0);
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

#include "breakout.h"
#include "iostream"
#include <tchar.h>

Breakout::Breakout()
{
	screen.SetTitle(_T("Engine Test"));
	gameData.Create(&hero);
	ball.hero = &hero;
	gameData.Create(&ball);
}
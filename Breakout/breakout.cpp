#include "breakout.h"
#include "snowflake.h"
#include "iostream"
#include <tchar.h>

Breakout::Breakout()
{
	screen.SetTitle(_T("Engine Test"));
	gameData.Create(&hero);
	ball.hero = &hero;
	gameData.Create(&ball);

	gameData.Create(&snowflakeManager);
}
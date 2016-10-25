#include "breakout.h"
#include "snowflake.h"
#include "iostream"
#include <tchar.h>

Breakout::Breakout()
{
	screen.SetTitle(_T("Engine Test"));
	gameData.Spawn(&hero);
	ball.hero = &hero;
	gameData.Spawn(&ball);

	gameData.Spawn(&snowflakeManager);
}
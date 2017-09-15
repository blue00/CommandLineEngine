#include "snowflake.h"
#include "..\CommandLineEngine\engine.h"

void Snowflake::Init(int x, int y, int ttl)
{
	posX = x;
	posY = y;
	look = "°";
	deathIn = ttl;
}

void Snowflake::Update()
{
	if (deathIn > 0)
	{
		engine->screen.SetString(posX, posY, look);

		if (--deathIn == 0)
		{
			alive = false;
		}
	}
}

const std::wstring Snowflake::ToString()
{
	return std::wstring(L"Snowflake");
}

#include "hero.h"
#include "..\CommandLineEngine\engine.h"  //"engine.h"

void Hero::Start()
{
	x = engine->screen.screenX / 2;
	y = engine->screen.screenY - 3;
	held = "####################";
}

//true falls der held getroffen wird. angle gibt den treffer"winkel" von -1 bis 1 zurück
bool Hero::CheckHit(float x, float y, float &angle)
{
	float length = held.length();

	if (y >= this->y)
	{
		float pos = x - this->x;

		if (pos >= 0 && pos <= length)
		{
			angle = ((pos - (length / (float)2)) / length) * 2;
			return true;
		}
	}

	return false;
}

void Hero::OnDestroy()
{

}

void Hero::Update()
{
	float length = static_cast<float>(held.length());

	//calculate x coordinate of hero
	x = engine->input.MousePos(engine->screen).x - length / 2.0f;

	//bounds checking for x coordinate
	if (x < 0)
	{
		x = 0;
	}
	else if (x + length > engine->screen.screenX)
	{
		x = engine->screen.screenX - length;
	}

	//draw held
	engine->screen.SetString(x, y, held);
}
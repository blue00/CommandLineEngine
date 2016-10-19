#include "Ball.h"
#include "..\CommandLineEngine\engine.h"
#include "hero.h"
#include "..\CommandLineEngine\mathf.h"

//struct Screen::Point; //forward declaration to use Screen:Point

void Ball::Start()
{
	look = "@";

	posX = 5;
	posY = 5;

	velX = 0.1;
	velY = 0.4;

	speed = 0.1;
}

void Ball::DrawTrail()
{
	float trailTime = 10;
	bool foundIt = false;

	//check if the current position is already part of the trail-vector, update timeLeft of all trails and remove all trails with timeLeft < 0
	for (std::vector<trail>::iterator it = trailVec.begin(); it != trailVec.end();)
	{
		if (it->x == posX && it->y == posY) //new point already listed? if yes reset timeLeft
		{
			it->timeLeft = trailTime / speed;
			foundIt = true;
		}
		else
		{
			it->timeLeft -= engine->deltaTime;
		}

		if (it->timeLeft < 0)
		{
			//erase returns the next object
			it = trailVec.erase(it);
		}
		else //we have to draw this trailpart and move to the next
		{
			engine->screen.SetString(it->x, it->y, look);
			++it;
		}
	}

	if (!foundIt) //new point? if yes add
	{
		trail newTrail;
		newTrail.timeLeft = trailTime / speed;
		newTrail.x = posX;
		newTrail.y = posY;
		trailVec.push_back(newTrail);
	}
}

void Ball::Update()
{
	/*
	
	was zu tun ist:	@TODO @DEBUG

	es gibt nun eine Raytrace-funktion in screen, diese gibt einem alle "pixel" zwischen 2 punkten.
	mit der hilfe dieser funktion kann nun ganz genau bestimmt werden ob etwas getroffen wurde
	
	da dies meistens mehrere pixel sind, muss die kollisionsprüfung in eine eigene funktion ausgelagert werden
	
	das testen ob ein block getroffen wurde ist nun kein problem mehr, da entweder die wand ODER ein block getroffen wird. es kann nicht mehr beides sein, für jede pixelprüfung

	anmerkung: in seltenen fällen bleibt der ball immer noch in den oberen ecken stecken, evtl kann das dann auch gelöst werden...
	*/
	engine->screen.SetString(0, 2, std::to_string(engine->deltaTime));
	engine->screen.SetString(0, 4, debugHeldHit);
	//velY = velY * 1.005; test for hit checking errors

	float posXNew = posX + velX * speed * engine->deltaTime;
	float posYNew = posY + velY * speed * engine->deltaTime;
	std::vector<Mathf::Point> visitedPoints = Mathf::Raytrace(posX, posY, posXNew, posYNew);
	//@TODO: use it now!

	float hitAngle;
	 
	//da wir hier zuerst gucken ob wir den helden getroffen haben, und dieser y-werte unter sich zulässt, kann der ball so das spielfeld bzw. das fenster verlassen
	if (hero->CheckHit(posXNew, posYNew, hitAngle)) //did we hit the held?
	{
		debugHeldHit = std::to_string(hitAngle);
		velY = -velY;
		velX = hitAngle; //@TODO: hier sollte die velocity rotiert werden, und nicht nur velX gesetzt werden. außerdem muss beachtet werden,
						//dass die Y-richtung immer schneller ist als die X-richtung, da mehr abstand zwischen unternanderliegenden zeichen ist.
						//dies könnte behoben werden indem es für y einen zusätzlichen wert gibt der immer auf das endergebnis addiert (oder malgenommen) wird
	}
	else if ((engine->screen.screenY - posYNew) < 0)
	{
		engine->screen.SetString(0, 1, "GAME OVER");
	}
	else if (!engine->screen.CheckBounds(posXNew, posYNew)) //we hit a wall
	{
		engine->screen.SetString(0, 1, "HIT");

		//change velocity
		if (posYNew < 0)
		{
			velY = -velY;
		}
		else
		{
			velX = -velX;
		}

		//recalculate new positions an check the bounds again. if we have a hit we are in an endless velocity change loop that we must solve
		if (!engine->screen.CheckBounds(posX + velX * speed, posY + velY * speed))
		{
			//solve endless velocity change
			if (posYNew < 0)
			{
				velX = -velX;
			}
			else
			{
				velY = -velY;
			}
		}
	}
	else
	{
		//move to new position
		posX = posXNew;
		posY = posYNew;
		//engine->screen.SetString(posX, posY, look);
	}

	DrawTrail();
}

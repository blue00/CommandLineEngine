#include "engine.h"

#include <time.h> //stopwatch
#include "Windows.h" //sleep
#include <string>
#include <iostream>

//abstract game class
Engine::Engine()
{
	gameData.engine = this;

	fixedTimeRate = 10;
	isFixedTimeOn = true;
}

void Engine::Run()
{
	clock_t startT, endT;

	while (true)
	{
		startT = clock(); //start auf aktuelle zeit setzen

		input.Tick(); //input ticken
		screen.Clear(); //screen clearen (ist doppelt gepuffert, daher muss daduch nicht unbedingt neu gezeichnet werden)
		gameData.Tick();
		screen.Draw(); //zeichnen (dadurch wird nicht immer zur gleichen zeit gezeichnet!)

		endT = clock() - startT; //dauer des ticks berrechnen

		if (isFixedTimeOn) //soll jeder tick mindestens fixedTimeRate lange dauern?
		{
			if (endT < fixedTimeRate) //war der tick zu schnell? falls ja warten
			{
				Sleep(fixedTimeRate - endT);
				deltaTime = fixedTimeRate;
				//system("Color 2B");
			}
			else
			{
				deltaTime = endT;
				//system("Color 3C");
			}
		}
		else
		{
			deltaTime = endT;
			//system("Color 4D");
		}
	}
}
#include "engine.h"

#include <time.h> // stopwatch
#include "Windows.h" // sleep
#include <string>
#include <iostream>

// abstract game class
Engine::Engine() :gameObjectManager(1 << 16)
{
	gameData.engine = this;

	fixedTimeRate = 10;
	isFixedTimeOn = true;
}

void Engine::Run()
{
	clock_t startT;
	float endT;

	while (true)
	{
		startT = clock();

		input.Tick();
		screen.Clear();
		gameData.Tick();
		screen.Draw(); // we do not draw to a consistent time this way... @DEBUG: can we solve this problem, maybe with an extra draw thread?

		endT = static_cast<float>(clock() - startT); // calculate tick duration time

		if (isFixedTimeOn)
		{
			if (endT < fixedTimeRate) //do we have to wait?
			{
				Sleep(int(fixedTimeRate - endT));
				deltaTime = fixedTimeRate;
				// system("Color 2B");
			}
			else
			{
				deltaTime = endT;
				// system("Color 3C");
			}
		}
		else
		{
			deltaTime = endT;
			// system("Color 4D");
		}
	}
}
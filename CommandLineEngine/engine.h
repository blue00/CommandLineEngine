#pragma once

#include "input.h"
#include "screen.h"
#include "audio.h"
#include "gameData.h"

class Engine
{
public:
	Engine();
	void Run(); //startet das spiel
	float fixedTimeRate;
	bool isFixedTimeOn;
	Input input;
	Screen screen;
	Audio audio;
	GameData gameData;
	float deltaTime; //die zeit die wärend des letzten ticks vergangen ist
};
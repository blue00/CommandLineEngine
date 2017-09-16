#pragma once

#include "input.h"
#include "screen.h"
#include "audio.h"
#include "gameData.h"
#include "gameObjectManager.h"

class Engine
{
public:
	Engine();
	void Run(); // start the game
	float fixedTimeRate;
	bool isFixedTimeOn;
	Input input;
	Screen screen;
	Audio audio;
	GameData gameData;
	GameObjectManager gameObjectManager;
	float deltaTime; // The time it took to complete the last frame @DEBUG: add unit
};
#pragma once

#include "gameObject.h"
#include <vector>
#include <iostream>

class Engine;

class GameData
{
public:
	Engine* engine;
	GameData();
	void Tick();
	void AddAlive(GameObject *gameObject);
	void AddUpdate(GameObject *gameObject);
	void RemoveUpdate(GameObject *gameObject);
	void Spawn(GameObject *gameObject);
	std::vector<GameObject*> updateVec; // vector of pointers to gameObjects
	std::vector<GameObject*> aliveVec;
};
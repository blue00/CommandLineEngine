#pragma once

#include "gameObjectToken.h"

class GameObject;

class GameObjectManager
{
public:
	GameObjectManager(int numEntitySlots);
	~GameObjectManager();
	void Register(GameObject* obj);
	void Unregister(GameObject* obj);
	GameObject* Get(GameObjectToken token);
	bool HasFreeSlots();
private:
	int numSlots;
	GameObject** entitySlots;

	int lastGivenId = 0;
	unsigned int lastGivenAbsoluteId = 0;

	int nextFreeSlot = 0;
	int getFreeSlot();
};
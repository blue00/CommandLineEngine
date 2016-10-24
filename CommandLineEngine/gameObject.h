#pragma once

#include <Windows.h>
#include <string>
#include "gameObjectToken.h"

class Engine;

class GameObject
{
public:
	bool alive = true;
	GameObject();
	~GameObject();
	void Initialize(Engine* engine);
	virtual void Update();
	virtual void Start();
	virtual void OnDestroy();
	GameObjectToken Token;
	Engine* engine;
	virtual const std::wstring ToString();
private:
};
#pragma once

#include <Windows.h>
#include <string>

class Engine;

class GameObject
{
public:
	bool alive = true;
	GameObject();
	~GameObject();
	Engine* engine;
	virtual void Update();
	virtual void Start();
	virtual void OnDestroy();
private:

};
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
	virtual void OnDestroy(); // @TODO: add private ondestroy function wich is called after OnDestroy to clean up the memory
    void Destroy();
	virtual const std::wstring ToString();
	GameObjectToken Token;
	Engine* engine;
protected:
private:
};
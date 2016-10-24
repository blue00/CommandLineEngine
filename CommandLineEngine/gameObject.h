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
	virtual void OnDestroy(); //@TODO: add private ondestroy function wich is called after OnDestroy to clean up the memory
    void Destroy();
private:

};
#pragma once

#include "gameObjectManager.h"
#include "gameObject.h"

template<class T>
struct GameObjectHandle
{
	T* GetObj();
	void SetObj(T* obj);

	GameObjectHandle();

private:
	GameObjectToken token;
	GameObjectManager* gameObjectManager = nullptr;
};
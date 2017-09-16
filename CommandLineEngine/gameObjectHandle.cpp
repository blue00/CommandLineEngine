#include "gameObjectHandle.h"

template<class T>
GameObjectHandle<T>::GameObjectHandle() :token(-1, 0)
{
}

template<class T>
T* GameObjectHandle<T>::GetObj()
{
	// check if invalid
	if (token.slotId == -1)
	{
		return nullptr;
	}

	GameObject* gameObject = gameObjectManager->Get(token);
	if (gameObject)
	{
		// farewell, static type safety
		return (T*)gameObject;
	}
	else
	{
		// no further lookups
		token.slotId = -1;
		return nullptr;
	}
}

// very important: we can only do that with objects that have already been spawned
template<class T>
void GameObjectHandle<T>::SetObj(T* obj)
{
	if (obj)
	{
		gameObjectManager = &(obj->engine->gameObjectManager);
		token = obj->Token;
	}
	else
	{
		token.slotId = -1;
	}
}
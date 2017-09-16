#include "gameObjectManager.h"
#include "gameObject.h"

#define SLOTS_ALL_FULL -2
#define SLOTS_UNKNOWN -1

GameObjectManager::GameObjectManager(int numEntitySlots)
{
	numSlots = numEntitySlots;
	entitySlots = new GameObject*[numSlots](); // puts nullptr in every slot
}

GameObjectManager::~GameObjectManager()
{
	delete entitySlots;
}

// checks if we have free slots. if we do, a fresh one is already standing by
bool GameObjectManager::HasFreeSlots()
{
	if (nextFreeSlot == SLOTS_UNKNOWN)
	{
		nextFreeSlot = getFreeSlot();
	}
	return nextFreeSlot != SLOTS_ALL_FULL;
}

// Get a free slot id or SLOTS_ALL_FULL if none was found
int GameObjectManager::getFreeSlot()
{
	for (int i = 0; i < numSlots; i++)
	{
		int id = (i + lastGivenId) % numSlots;
		if (!entitySlots[id])
		{
			return id;
		}
	}

	// no more space
	return SLOTS_ALL_FULL;
}

// Register a GameObject so it can use the token system
void GameObjectManager::Register(GameObject* obj)
{
	OutputDebugStringW(L"Registering ");
	OutputDebugStringW((obj->ToString()).c_str());
	OutputDebugStringW(L"... ");

	if (!HasFreeSlots())
	{
		OutputDebugStringW(L"failed\n");
		MessageBox(NULL, L"No more entity slots, this will be fatal!", NULL, NULL);
		// i wanna throw an exception but i don't know how to do that properly in c++. i'm dumb @DEBUG: do it properly
	}
	else
	{
		// found a free slot
		lastGivenId = nextFreeSlot;
		entitySlots[nextFreeSlot] = obj;

		GameObjectToken token(nextFreeSlot, lastGivenAbsoluteId++);
		obj->Token = token;

		OutputDebugStringW(L"SlotIndex: ");
		OutputDebugStringW(std::to_wstring(token.slotId).c_str());
		OutputDebugStringW(L" | AbsID: ");
		OutputDebugStringW(std::to_wstring(token.absoluteId).c_str());
		OutputDebugStringW(L"\n");

		nextFreeSlot = SLOTS_UNKNOWN;
	}
}

// Unregister a GameObject. Its tokens will return nullptr from now on.
void GameObjectManager::Unregister(GameObject* obj)
{
	OutputDebugStringW(L"Unregistering ");
	OutputDebugStringW((obj->ToString()).c_str());
	OutputDebugStringW(L"\n");

	GameObjectToken token = obj->Token;
	GameObject* presumedObj = Get(token);
	if (presumedObj != obj)
	{
		// BAD BAD BAD
		MessageBox(NULL, L"Attempted to unregister an object which is not registered!", NULL, NULL);
		// i wanna throw an exception but i don't know how to do that properly in c++. i'm dumb
	}
	else
	{
		entitySlots[token.slotId] = nullptr;

		// if we didn't have space before, now we do
		if (nextFreeSlot == SLOTS_ALL_FULL)
		{
			nextFreeSlot = token.slotId;
		}
	}
}

// Get a GameObject based on the given token. (or nullptr if it doesn't exist)
GameObject* GameObjectManager::Get(GameObjectToken token)
{
	// check range (is "out of range" an error?)
	if (token.slotId < 0 || token.slotId >= numSlots)
	{
		// i wanna throw an exception but i don't know how to do that properly in c++. i'm dumb @DEBUG: do it properly
		return nullptr;
	}

	GameObject* currentObj = entitySlots[token.slotId];

	if (currentObj && currentObj->Token.absoluteId == token.absoluteId)
	{
		return currentObj;
	}
	else
	{
		return nullptr;
	}
}

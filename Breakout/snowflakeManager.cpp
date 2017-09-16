#include "snowflakeManager.h"
#include "..\CommandLineEngine\engine.h"

void SnowflakeManager::Start()
{
	nextX = 30;
	nextY = 10;
	GameObject::Start();
}

void SnowflakeManager::Update()
{
	Snowflake* snowflake = handle.GetObj();
		
	// of course you don't really need to check HasFreeSlots() each time you want to spawn a new object
	if (!snowflake && engine->gameObjectManager.HasFreeSlots())
	{
		snowflake = new Snowflake();
		snowflake->Init(nextX, nextY, 100);
		nextX++;
		if (nextX > 60)
		{
			nextY++;
			nextX = 30;
		}

		engine->gameData.Spawn(snowflake);
		handle.SetObj(snowflake);
	}
}

const std::wstring SnowflakeManager::ToString()
{
	return std::wstring(L"Snowflake Manager");
}

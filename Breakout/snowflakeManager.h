#pragma once

#include "..\CommandLineEngine\gameObject.h"
#include <string>
#include "snowflake.h"
#include "../CommandLineEngine/gameObjectHandle.cpp"

class SnowflakeManager : public GameObject
{
public:
	virtual void Update();
	virtual void Start();
	virtual const std::wstring ToString();
private:
	GameObjectHandle<Snowflake> handle;
	int nextX, nextY;
};

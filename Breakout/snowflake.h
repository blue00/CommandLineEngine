#pragma once

#include "..\CommandLineEngine\gameObject.h"
#include <string>

class Snowflake : public GameObject
{
public:
	void Init(int x, int y, int ttl);

	virtual void Update();
	// virtual void Start();
	virtual const std::wstring ToString();
private:
	int posX;
	int posY;
	int deathIn;
	std::string look;
};

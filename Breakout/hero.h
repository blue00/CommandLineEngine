#pragma once

#include "..\CommandLineEngine\gameObject.h"
#include <string>

class Hero : public GameObject
{
public:
	float x;
	float y;
	std::string held;

	virtual void Update();
	virtual void OnDestroy();
	virtual void Start();

	bool CheckHit(float x, float y, float& angle);
};

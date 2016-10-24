#pragma once

#include "..\CommandLineEngine\gameObject.h"
#include <string>
#include <vector>

class Hero;

class Ball : public GameObject
{
public:
	float posX;
	float posY;
	float velX;
	float velY;
	float speed;

	virtual void Update();
	virtual void Start();
	virtual const std::wstring ToString();

	Hero* hero;
private:
	std::string look;
	struct trail
	{
		int x = 0;
		int y = 0;
		float timeLeft = 0;
	};
	std::vector<trail> trailVec;
	std::string debugHeldHit;
	void DrawTrail();
};


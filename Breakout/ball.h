#pragma once

#include "..\CommandLineEngine\gameObject.h"
#include <string>
#include <vector>

class Hero;

class Ball : public GameObject
{
public:
	std::string  look;
	float posX;
	float posY;
	float velX;
	float velY;
	float speed;

	virtual void Update();
	virtual void Start();

	Hero* hero;
private:
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


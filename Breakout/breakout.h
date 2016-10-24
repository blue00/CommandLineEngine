#pragma once

#include "..\CommandLineEngine\engine.h"

#include "ball.h"
#include "hero.h"
#include "snowflakeManager.h"

class Breakout : public Engine
{
public:
	Breakout();
private:
	Hero hero;
	Ball ball;
	SnowflakeManager snowflakeManager;
};
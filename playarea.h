#pragma once
#include "object.h"
#include "asteroid.h"
#include "playercraft.h"
#include "enemycraft.h"

class playarea :
	public object
{
public:
	asteroid* asteroids = nullptr;
	int nasteroids = 0;

	playercraft* player = nullptr;
	
	enemycraft* enemies = nullptr;
	int nenemies = 0;
	
	playarea();
	~playarea();

	void script() override;
};


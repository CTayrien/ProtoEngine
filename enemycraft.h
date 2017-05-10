#pragma once
#include "object.h"
#include "playercraft.h"

class enemycraft :
	public object
{
public:
	playercraft* player = nullptr;
	bool isactive = false;

	enemycraft();
	~enemycraft();

	void script() override;
};


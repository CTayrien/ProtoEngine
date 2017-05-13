#pragma once
#include "object.h"
#include "rollaball.h"

class collectible :
	public object
{
public:
	rollaball* player = nullptr;

	collectible();
	~collectible();
	void script() override;
};


#pragma once
#include "object.h"
#include "rollaball.h"

class collectible :
	public object
{
public:
	bool isactive = true;
	rollaball* player = nullptr;
	collectible();
	~collectible();
	void script() override;
};


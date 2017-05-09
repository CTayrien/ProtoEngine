#pragma once
#include "object.h"
class collectible :
	public object
{
public:
	bool isactive = true;
	collectible();
	~collectible();
};


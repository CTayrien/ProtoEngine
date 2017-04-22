#pragma once
#include "object.h"
class Arrow :
	public object
{
public:
	Arrow();
	~Arrow();
	void update() override;
};


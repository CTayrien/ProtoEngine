#pragma once
#include "object.h"
class Arrow :
	public object
{
public:
	Arrow();
	virtual ~Arrow();
	void update() override;
};


#pragma once
#include "object.h"

class shark :
	public object
{
public:
	shark();
	~shark();

	object* shoal;
	void script() override;
};
#pragma once
#include "object.h"
class spacecraft :
	public object
{
public:
	spacecraft();
	spacecraft(model* mod, texture* tex);
	~spacecraft() override;
	void script() override;
};


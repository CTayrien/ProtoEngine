#pragma once
#include "object.h"

class moon :
	public object
{
public:
	moon();
	moon(model* mod, texture* tex);

	~moon() override;

	void script() override;
};


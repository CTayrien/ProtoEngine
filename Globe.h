#pragma once
#include "object.h"
class Globe :
	public object
{
public:
	Globe();
	~Globe();
	void update() override;
};


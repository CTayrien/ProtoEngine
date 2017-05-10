#pragma once
#include "object.h"
#include "playercraft.h"

class asteroid :
	public object
{
public:
	playercraft* player = nullptr;
	bool isactive = false;

	asteroid();
	~asteroid();

	void script() override;
};


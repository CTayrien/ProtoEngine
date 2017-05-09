#pragma once
#include "object.h"
#include "collectible.h"

class rollaball :
	public object
{
public:
	int score = 0;
	collectible* collectibles = nullptr;
	int ncollectibles = 0;

	void script() override;
	rollaball();
	~rollaball();
};


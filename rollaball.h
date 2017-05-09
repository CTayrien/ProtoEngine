#pragma once
#include "object.h"

class rollaball :
	public object
{
public:
	int score = 0;

	void script() override;
	rollaball();
	~rollaball();
};


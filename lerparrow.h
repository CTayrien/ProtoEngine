#pragma once
#include "Arrow.h"
class lerparrow :
	public Arrow
{
public:
	transform* a;
	transform* b;
	float f = 1.0f/3.0f;
	float t = 0.0f;
	float d = 1.0f;
	bool go = true;

	lerparrow();
	~lerparrow();
	void update() override;
};


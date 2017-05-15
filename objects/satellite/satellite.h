#pragma once
#include "object.h"

class satellite :
	public object
{
public:
	object* player;
	float pi = 3.14159;
	float phase = 0;
	float t = 0;
	float rorbit = 4;
	float period = 4;
	glm::vec3 c() { return player->tform.loc; }

	satellite(object* player, float phase);
	~satellite();

	void script() override;
};
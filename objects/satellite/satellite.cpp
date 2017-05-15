#include "satellite.h"
#include "engine.h"

satellite::satellite(object* player, float phase)
{
	tag = "satellite";
	mod = model({ "engine/models/sphere.dat" });
	tex = texture({ "engine/textures/red.png" });
	this->player = player;
	this->phase = phase;
}

satellite::~satellite()
{
}

void satellite::script()
{
	t += engine::timer.dt;

	float x = rorbit * cosf(2 * pi * (t / period + phase));
	float y = rorbit * sinf(2 * pi * (t / period + phase));

	tform.loc = c() + glm::vec3{x, y, 0};
}
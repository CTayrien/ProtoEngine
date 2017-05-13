#include "collectible.h"
#include "engine\engine.h"
#include <iostream>

collectible::collectible()
{
	tag = "collectible";
	mod = model({ "engine/models/box.dat" });
	tex = texture({ "engine/textures/blue.png" });
	tform.scale = { .1, .1, .1 };
	tform.rotvel = { 1,1,1 };
}

collectible::~collectible()
{
}

void collectible::script()
{
	if (collides<BOX, SPHERE>(*player)) {
		garbage = true;
		std::cout << "Nice! Score: " << ++player->score << std::endl;
		if (player->score == 10) {
			std::cout << "A winner is you!!!!1" << std::endl;
			glfwSetWindowShouldClose(engine::window.ptr, GLFW_TRUE);
		}
	}

	// this code should be on transform, but then the earth doesn't rotate properly (at all)
	tform.rotvel += tform.torque / tform.moment * engine::timer.dt;
	tform.rot += tform.rotvel * engine::timer.dt;
	tform.torque = { 0, 0, 0 };
	tform.setyawpitchroll(tform.rot);
}
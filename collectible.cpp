#include "collectible.h"
#include "engine\engine.h"
#include <iostream>

collectible::collectible()
{
}

collectible::~collectible()
{
}

void collectible::script()
{
	if (isactive && collides<BOX, SPHERE>(*player)) {
		engine::scene.remove(this);
		std::cout << "Nice! Score: " << ++player->score << std::endl;
		isactive = false;
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
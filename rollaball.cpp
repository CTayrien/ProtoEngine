#include "rollaball.h"
#include "engine\engine.h"
#include <iostream>

void rollaball::script()
{
	//std::cout << "Timer: " << engine::timer.t << std::endl;
	//if (engine::timer.t > 10) {
	//	engine::stop("You collected: " + score);
	//}

	for (int i = 0; i < ncollectibles; i++) {
		if (collectibles[i].isactive && collectibles[i].collides<BOX, SPHERE>(*this)) {
			engine::scene.remove(&collectibles[i]);
			std::cout << ++score;
			collectibles[i].isactive = false;
		}
	}

	if (engine::input.ddown[input_tilde] == 1) engine::camera.toggledebug();
	if (engine::camera.isdebug) return;

	float power = 1;
	glm::vec3 d;
	if (engine::input.down[input_w]) d.z--;
	if (engine::input.down[input_a]) d.x--;
	if (engine::input.down[input_s]) d.z++;
	if (engine::input.down[input_d]) d.x++;
	if (d != glm::vec3()) d = glm::normalize(d);
	tform.force += d * power;

	float drag = 1;
	tform.force -= tform.vel * tform.vel * drag;
}

rollaball::rollaball()
{
}


rollaball::~rollaball()
{
}

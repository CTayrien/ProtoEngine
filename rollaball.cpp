#include "rollaball.h"
#include "engine\engine.h"
#include <iostream>

void rollaball::script()
{
	// Drag - should be on tform?
	glm::vec3 d = tform.vel;
	if (d != glm::vec3()) d = glm::normalize(d);
	float x = glm::length(tform.vel);
	float a = 1, b = 1, c = 1;
	tform.force -= d * (a * x * x + b * x + c);

	// Toggle control (ball vs debug cam)
	if (engine::input.ddown[input_tilde] == 1) engine::camera.toggledebug();
	if (engine::camera.isdebug) return;

	// Move
	float power = 80;
	glm::vec3 md;
	if (engine::input.down[input_w]) md.y++;
	if (engine::input.down[input_a]) md.x--;
	if (engine::input.down[input_s]) md.y--;
	if (engine::input.down[input_d]) md.x++;
	if (md != glm::vec3()) md = glm::normalize(md);
	tform.force += md * power;

	// Roll - should be a delta-rotate function on tform?
	if (tform.vel == glm::vec3()) return;
	float radius = 1;
	float angle = glm::length(tform.vel) * radius * engine::timer.dt;
	glm::vec3 axis = glm::normalize(glm::cross(glm::vec3(0, 0, 1), tform.vel));
	tform.R = glm::mat3(glm::rotate(angle, axis)) * tform.R;
}

rollaball::rollaball()
{
}


rollaball::~rollaball()
{
}

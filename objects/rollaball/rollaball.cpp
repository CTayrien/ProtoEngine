/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "rollaball.h"
#include "engine.h"
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
	if (engine::cam.isdebug) return;

	// Move
	float power = 80;
	glm::vec3 md;
	md.y += engine::input.down[input_w];
	md.x -= engine::input.down[input_a];
	md.y -= engine::input.down[input_s];
	md.x += engine::input.down[input_d];
	tform.force += transform::norm(md) * power;

	// concatenate delta rotation, from rodriguez, in world space, pre-multiplied (post-multiplied in model space from tait-bryant works for dogfight cam)
	float radius = mod.r * tform.scale.x;
	float angvelmag = glm::length(tform.vel) * radius;
	
	float angle = angvelmag * engine::timer.dt;
	glm::vec3 axis = transform::norm(glm::cross(glm::vec3(0, 0, 1), tform.vel));
	
	tform.R = transform::rodrigz(axis, angle) * tform.R;
}

rollaball::rollaball()
{
	tag = "player";
	mod = model({ "engine/models/sphere.dat" });
	tex = texture({ "engine/textures/earth.png" });
}

rollaball::~rollaball()
{
}
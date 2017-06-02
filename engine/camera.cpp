/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "camera.h"
#include "engine.h"

camera::camera()
{
	tag = "camera";
	mod = model({ "engine/models/camera.dat" });
	tex = texture({ "engine/textures/black.png" });
	tform.loc.z = 10;
}

camera::~camera()
{
}

void camera::toggledebug()
{
	setdebug(!isdebug);
}

void camera::setdebug(bool isdebug)
{
	this->isdebug = isdebug;
	if (engine::window.ptr) glfwSetInputMode(engine::window.ptr, GLFW_CURSOR, (isdebug) ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
	tform.vel = glm::vec3();
}

void camera::script()
{
	if (engine::input.ddown[input_tilde] == 1)
	{
		toggledebug();
		if (!isdebug) {
			printf("loc: %f, %f, %f", tform.loc.x, tform.loc.y, tform.loc.z);
		}
		else {
			printf("\nDebug cam on.\n");
		}
	}
		
	if (isdebug) {
		if (engine::input.down[input_esc])
			glfwSetWindowShouldClose(engine::window.ptr, true);
		debugmove();
		debugturn();
	}
}

bool camera::load()
{
	perspective = glm::perspective(transform::pi * .4f,		//fov
		(float)engine::window.w / (float)engine::window.h,	//aspect ratio
		.01f,												//z near
		1000.f);											//z far

	setdebug(isdebug);

	return object::load();
}

void camera::uploadpov()
{
	// World-view transform & lighting
	glUniformMatrix4fv(5, 1, GL_FALSE, &(perspective * glm::lookAt(tform.loc, tform.lookat(), tform.up()))[0][0]);
	glUniform3fv(6, 1, &tform.loc[0]);
}

// Aggregate direction vector and apply normalized if non-zero
void camera::debugmove()
{
	glm::vec3 d;

	d.z -= engine::input.down[input_w];
	d.x -= engine::input.down[input_a];
	d.z += engine::input.down[input_s];
	d.x += engine::input.down[input_d];
	d.y -= engine::input.down[input_ctrl];
	d.y += engine::input.down[input_space];

	//if (d != glm::vec3())
		tform.vel = tform.R * transform::norm(d) * maxspeed;
	
	/*
	if (engine::input.down[input_shift])
		maxspeed = pow(maxspeed, 1+engine::timer.dt);
	
	float speed = glm::length(tform.vel);
	// if user not pushing button
	if (d == glm::vec3()) {
		if (speed == 0) {
			maxspeed = 2;	//not moving: reset maxspeed
		}
		else {
			glm::vec3 dir = transform::norm(tform.vel);
			float t = speed/maxspeed - engine::timer.dt;
			if (t < 0) t = 0;

			tform.vel = tform.R * glm::mix(dir * maxspeed, glm::vec3(), t);
		}
	}
	/**/
}

void camera::debugturn()
{	
	// Switch to drotin for dogfight controls instead of fps controls
	tform.drotex(glm::vec3(
		-sens * engine::input.cursor.dy,
		-sens * engine::input.cursor.dx,
		0));

	engine::input.cursor.clamp();
}
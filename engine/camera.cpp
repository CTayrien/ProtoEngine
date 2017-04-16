/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "camera.h"
#include "engine.h"

camera::camera()
{
	tag = "camera";
	mod = new model("engine/models/camera.dat");
	tex = new texture("engine/textures/black.png");
	tform.loc.y = 2;
	tform.rot.x = -engine::pi / 2;
	fov = engine::pi * .4f;
}

camera::~camera()
{
	delete mod;
	delete tex;
}

bool camera::start()
{
	// Hide cursor
	glfwSetInputMode(window::ptr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// Move cursor to center
	glfwSetCursorPos(window::ptr, window::halfw, window::halfh);

	mod->load();
	if (!mod->loaded) return false;

	tex->load();
	if (!tex->loaded) return false;

	return true;
}

void camera::update()
{
	tform.update();

	move();
	
	turn();

	upload();
}

void camera::upload()
{
	worldView = glm::perspective(fov, aspect, zNear, zFar)
		* glm::lookAt(tform.loc, tform.loc + tform.forward(), tform.up());

	glUniformMatrix4fv(4, 1, GL_FALSE, &worldView[0][0]);

	// for lighting
	glUniform3fv(6, 1, &tform.loc[0]);
}

void camera::move()
{
	// Move
	glm::vec3 d;

	if (input::isDown(input_w)) d.z -= 1;
	if (input::isDown(input_a)) d.x -= 1;
	if (input::isDown(input_s)) d.z += 1;
	if (input::isDown(input_d)) d.x += 1;

	float d2 = glm::dot(d, d);
	if (d2 != 0) d /= d2;
	
	tform.vel = tform.R * d * maxspeed;
}

void camera::turn()
{
	// Yaw & Pitch (pitch clamped to +/- 90 deg)
	tform.rot.y -= sens * window::dx;
	tform.rot.x -= sens * window::dy;
	tform.rot.x = glm::clamp(tform.rot.x, -engine::pi/2, engine::pi/2);
}

void camera::stop()
{
	mod->unload();
	tex->unload();
}
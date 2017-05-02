/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "camera.h"
#include "engine.h"

camera::camera()
{
	tag = "camera";
	mod = new model("engine/models/camera2.dat");
	tex = new texture("engine/textures/black.png");
	fov = engine::pi * .4f;
	tform.loc.z = 2;
	tform.rot = glm::vec3{};
}

camera::~camera()
{
	delete mod;
	delete tex;
}

//void camera::toggleisfps()
//{
//	setisfps(!isfps);
//}

void camera::setisfps(bool isfps)
{
	this->isfps = isfps;
	int value = (isfps) ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL;
	glfwSetInputMode(engine::window.ptr, GLFW_CURSOR, value);
}

bool camera::start()
{
	// Hide cursor
	setisfps(isfps);

	aspect = (float)engine::window.w / (float)engine::window.h;

	load();

	return true;
}

void camera::script()
{
	if (isfps) {
		move();
		turn();
	}

	upload();
}

void camera::updatematrix()
{
	worldView = glm::perspective(fov, aspect, zNear, zFar)
		* glm::lookAt(tform.loc, tform.loc + tform.forward(), tform.up());
}

void camera::upload()
{
	// Bake this in?
	updatematrix();

	// World-view transform
	glUniformMatrix4fv(4, 1, GL_FALSE, &worldView[0][0]);

	// Lighting uniform variable
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
	if (d2 != 0) d /= d2;	//sqrt d2?
	
	tform.vel = tform.R * d * maxspeed;
}

void camera::turn()
{
	engine::window.clampcursor();

	// Yaw & Pitch (pitch clamped to +/- 90 deg)
	tform.rot.y -= sens * (float)engine::window.dx;
	tform.rot.x -= sens * (float)engine::window.dy;
	tform.rot.x = glm::clamp(tform.rot.x, -engine::pi/2, engine::pi/2);
}

void camera::stop()
{
	unload();
}
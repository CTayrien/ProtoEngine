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
	tform.loc.z = 2;
	tform.rot = glm::vec3{};
}

camera::~camera()
{
	delete mod;
	delete tex;
}

void camera::setisfps(bool isfps)
{
	this->isfps = isfps;
	glfwSetInputMode(engine::window.ptr, GLFW_CURSOR, (isfps) ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL);
	tform.vel = glm::vec3();
}

void camera::script()
{
	if (isfps) {
		flymove();
		flyturn();
	}

	if (ispov) {
		// Shader objects render
		engine::theshader.use();
		upload();

		// Skybox shader camera and skybox at origin
		engine::shader_skybox.use();
		glm::vec3 temp = tform.loc;
		tform.loc = glm::vec3();
		upload();
		tform.loc = temp;
	}
}

void camera::render()
{
	if (!ispov) object::render();
}

void camera::load()
{
	perspective = glm::perspective(engine::pi * .4f,		//fov
		(float)engine::window.w / (float)engine::window.h,	//aspect ratio
		.01f,												//z near
		1000.f);											//z far

	setisfps(isfps);

	object::load();
}

void camera::upload()
{
	worldView = perspective	* glm::lookAt(tform.loc, tform.loc + tform.forward(), tform.up());

	// World-view transform
	glUniformMatrix4fv(4, 1, GL_FALSE, &worldView[0][0]);

	// Lighting uniform variable
	glUniform3fv(6, 1, &tform.loc[0]);
}

void camera::flymove()
{
	glm::vec3 d;
	if (engine::isdown(input_w)) d.z -= 1;
	if (engine::isdown(input_a)) d.x -= 1;
	if (engine::isdown(input_s)) d.z += 1;
	if (engine::isdown(input_d)) d.x += 1;
	//up and down w/ space and ctrl?

	// Try to normalize
	float len = glm::length(d);
	if (len != 0) d /= len;
	
	tform.vel = tform.R * d * maxspeed;
}

void camera::flyturn()
{
	double &x = engine::cursor.x, &y = engine::cursor.y, &x0 = engine::cursor.x0, &y0 = engine::cursor.y0;

	// Yaw & Pitch (pitch clamped to +/- 90 deg)
	tform.rot.y -= sens * (float)(x - x0);
	tform.rot.x -= sens * (float)(y - y0);
	tform.rot.x = glm::clamp(tform.rot.x, -engine::pi/2, engine::pi/2);

	// Clamp cursor to window
	glfwSetCursorPos(engine::window.ptr,
		glm::clamp((int)x, 0, engine::window.w),
		glm::clamp((int)y, 0, engine::window.h));
	glfwGetCursorPos(engine::window.ptr, &x, &y);
	x0 = x; y0 = y;
}
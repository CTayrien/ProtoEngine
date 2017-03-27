/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "camera.h"
#include "engine.h"

camera::camera()
{
	tag = "camera";
	mod = new model("engine/models/camera.obj");
	tex = new texture("engine/textures/black.png");
	tform.loc.z = 1.5;
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

	if (!mod->load())
		return false;

	if (!tex->load())
		return false;

	return true;
}

void camera::update()
{
	tform.update();

	move();
	
	turn();

	worldView = glm::perspective(fov, aspect, zNear, zFar) 
		* glm::lookAt(tform.loc, tform.loc + tform.forward(), tform.up());

	upload();
}

void camera::upload()
{
	glUniformMatrix4fv(4, 1, GL_FALSE, &worldView[0][0]);

	// for lighting
	glUniform3fv(6, 1, &tform.loc[0]);
}

void camera::move()
{
	// Move
	glm::vec3 v;

	if (input::isDown(GLFW_KEY_LEFT))  v.x -= 1;
	if (input::isDown(GLFW_KEY_RIGHT)) v.x += 1;
	if (input::isDown(GLFW_KEY_UP))    v.z -= 1;
	if (input::isDown(GLFW_KEY_DOWN))  v.z += 1;

	tform.vel = (v == glm::vec3()) ? glm::vec3() : tform.R * glm::normalize(v) * maxvel;	// velocity-based move
	//tform.force += (v != glm::vec3()) ? R * glm::normalize(v) * maxvel : glm::vec3();	// force-based move
}

void camera::turn()
{
	// Yaw 
	tform.rot.y += sens * (window::halfw - window::cursorx);

	// Pitch (clamped to +/- 90 deg)
	tform.rot.x += sens * (window::halfh - window::cursory);
	tform.rot.x = glm::clamp(tform.rot.x, -engine::pi/2, engine::pi/2);
	
	// Move cursor to center screen so user stops turning, unless they move mouse again.
	glfwSetCursorPos(window::ptr, window::halfw, window::halfh);
}

void camera::stop()
{
	mod->unload();
	tex->unload();
}
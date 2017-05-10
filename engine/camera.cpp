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
	tform.loc.z = 2;
	tform.rot = glm::vec3{};
}

camera::~camera()
{
	delete mod;
	delete tex;
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
			printf("Yaw, Pitch, Roll: %f, %f, %f", tform.rot.x, tform.rot.y, tform.rot.z);
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

void camera::render()
{
	if (ispov) {
		uploadpov();
	}
	if (!ispov){
		object::render();
	}
}

void camera::load()
{
	perspective = glm::perspective(engine::pi * .4f,		//fov
		(float)engine::window.w / (float)engine::window.h,	//aspect ratio
		.01f,												//z near
		1000.f);											//z far

	setdebug(isdebug);

	object::load();
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

	if (engine::input.down[input_w]) d.z -= 1;
	if (engine::input.down[input_a]) d.x -= 1;
	if (engine::input.down[input_s]) d.z += 1;
	if (engine::input.down[input_d]) d.x += 1;
	if (engine::input.down[input_ctrl]) d.y -= 1;
	if (engine::input.down[input_space]) d.y += 1;

	if (d != glm::vec3()) d = glm::normalize(d);
	tform.vel = tform.R * d * maxspeed;
}

void camera::debugturn()
{
	// Yaw & Pitch (pitch clamped to +/- 90 deg)
	tform.rot.y -= sens * engine::cursor.dx;
	tform.rot.x -= sens * engine::cursor.dy;
	tform.rot.x = glm::clamp(tform.rot.x, -engine::pi/2, engine::pi/2);
	
	tform.setyawpitchroll(tform.rot);
	
	// Should be possible to store / modify a quaternion instead? If I can, then transform.rot is obsolete class data. Should be able to set yaw pitch roll, and add delta yaw pitch roll. May need to derive ypr from q
	glfwSetCursorPos(engine::window.ptr,
		glm::clamp((int)engine::cursor.x, 0, engine::window.w),
		glm::clamp((int)engine::cursor.y, 0, engine::window.h));
	
	engine::cursor.update();
}
/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "engine.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// static member data constructor call (ish)
timer engine::time;
camera engine::cam;
light engine::light;
skybox engine::skybox;

bool engine::start()
{
	// Init engine's libraries, window, renderer, input, physics timer
	//		make window name, size, etc. variables, let game dev set them
	if (glfwInit() != GL_TRUE)	return false;
	
	if (!window::start()) return false;
	
	if (glewInit() != GLEW_OK) return false;

	time.start();

	if (!input::start()) return false;
	
	if (!renderer::start()) return false;

	cam.start();

	//light.start();

	skybox.start();

	return true;
}

void engine::update()
{	
	renderer::update();

	window::update();

	time.update();
	
	input::update();

	cam.update();

	skybox.update();

	light.update();
}

void engine::stop()
{
	renderer::stop();
	
	window::stop();

	skybox.stop();
}
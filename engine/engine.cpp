/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "engine.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Variables declared static in engine class namespace, but allocated/instantiated once in global memory
float engine::pi = glm::pi<float>();
timer engine::time;

camera engine::cam;
skybox engine::skybox;

shader engine::theshader("engine/shaders/vshader.glsl", "engine/shaders/fshader.glsl");
shader engine::shader_skybox("engine/shaders/vshader_skybox.glsl", "engine/shaders/fshader_skybox.glsl");

window engine::window;

bool engine::inputdown(int key)
{
	return GLFW_PRESS == glfwGetKey(window.ptr, key);
}

bool engine::start()
{
	window.start();
	
	theshader.tryload();
	shader_skybox.tryload();

	theshader.use();

	// Scene basics
	cam.start();
	skybox.start();

	time.start();

	return true;
}

void engine::update()
{	
	time.update();
	
	window.update();
	
	skybox.render();
	
	cam.update();

	skybox.update();
}

void engine::stop()
{
	theshader.unload();

	shader_skybox.unload();
	
	window.stop();
}
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
light engine::light;
skybox engine::skybox;
shader engine::theshader("engine/shaders/vshader.glsl", "engine/shaders/fshader.glsl");
shader engine::shader_skybox("engine/shaders/vshader_skybox.glsl", "engine/shaders/fshader_skybox.glsl");
material engine::thematerial;

window engine::window;

bool engine::start()
{
	// Init engine's libraries, window, renderer, input, physics timer
	//		make window name, size, etc. variables, let game dev set them

	// really should have a component model - is the scene one of the components?
	if (glfwInit() != GL_TRUE)	return false;

	window.ptr = glfwCreateWindow(window.w, window.h, window.title.c_str(), NULL, NULL); //glfwGetPrimaryMonitor(), NULL
	
	if (nullptr == window.ptr) return false;
	
	glfwMakeContextCurrent(window.ptr);
	
	if (glewInit() != GLEW_OK) return false;

	time.start();

	if (!input::start()) return false;
	
	// Renderer basics
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(.45f, .45f, .9f, 1.f);

	theshader.tryload();
	shader_skybox.tryload();
	if (!theshader.loaded || !shader_skybox.loaded)
		return false;

	theshader.use();
	thematerial.use();

	// Scene basics
	cam.start();
	skybox.start();

	return true;
}

void engine::update()
{	
	// Send color buffer to screen, clear new frame buffers
	glfwSwapBuffers(window.ptr);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// should this be somewhere else?
	skybox.render();

	// Process queued changes to window and input
	glfwPollEvents();

	window.update();

	time.update();
	
	input::update();

	cam.update();

	skybox.update();

	light.update();
}

void engine::stop()
{
	theshader.unload();
	shader_skybox.unload();

	glfwTerminate();

	skybox.stop();

	cam.stop();
}
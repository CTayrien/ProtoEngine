/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "engine.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Variables declared static in engine class namespace, but allocated/instantiated once in global memory
float engine::pi = glm::pi<float>();

// input
bool engine::isdown(int key) {
	return GLFW_PRESS == glfwGetKey(window.ptr, key);
}

cursor engine::cursor;
window engine::window;
timer engine::timer;

// renderer assets
shader engine::theshader("engine/shaders/vshader.glsl", "engine/shaders/fshader.glsl");
shader engine::shader_skybox("engine/shaders/vshader_skybox.glsl", "engine/shaders/fshader_skybox.glsl");

// scene objects
camera engine::camera;
skybox engine::skybox;

bool engine::start()
{
	if (glfwInit() != GL_TRUE) { return false; }
	window.ptr = glfwCreateWindow(window.w, window.h, window.title.c_str(), NULL, NULL); //glfwGetPrimaryMonitor(), NULL
	if (nullptr == window.ptr) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window.ptr);
	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return false;
	}

	// Renderer settings
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(.45f, .45f, .9f, 1.f);

	theshader.tryload();
	shader_skybox.tryload();

	camera.start();
	camera.load();
	camera.setisfps(true);

	skybox.load();
	skybox.tform.derivematrix();

	return true;
}

void engine::update()
{	
	// End old scene, start new one
	glfwSwapBuffers(window.ptr);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwPollEvents();

	timer.t += timer.dt = (float)(glfwGetTime() - timer.t);
	
	cursor.x0 = cursor.x; cursor.y0 = cursor.y;
	glfwGetCursorPos(window.ptr, &cursor.x, &cursor.y);

	// scene.update
	camera.update();
	skybox.update();
	
	// scene.render
	camera.render();
	skybox.render();
}

void engine::stop()
{
	theshader.unload();
	shader_skybox.unload();
	
	skybox.unload();
	camera.unload();

	glfwTerminate();
}
/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "engine.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Variables declared static in engine class namespace, but allocated/instantiated once in global memory
float engine::pi = glm::pi<float>();

// Input
bool engine::isdown(int key) {
	return GLFW_PRESS == glfwGetKey(window.ptr, key);
}

cursor engine::cursor;
window engine::window;
timer engine::timer;

// Scene renderer assets
shader engine::theshader("engine/shaders/vshader.glsl", "engine/shaders/fshader.glsl");
shader engine::shader_skybox("engine/shaders/vshader_skybox.glsl", "engine/shaders/fshader_skybox.glsl");

// Scene objects
camera engine::camera;
skybox engine::skybox;
scene engine::scene;

void engine::start()
{
	// Start window w/ GLFW & start GLEW
	if (glfwInit() != GL_TRUE) { stop("GLFW init failed"); }
	window.ptr = glfwCreateWindow(window.w, window.h, window.title.c_str(), NULL, NULL); //glfwGetPrimaryMonitor(), NULL
	if (nullptr == window.ptr) { stop("GLFW create window failed"); }
	glfwMakeContextCurrent(window.ptr);
	if (glewInit() != GLEW_OK) { stop("GLEW init failed"); }

	// Renderer settings
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(.45f, .45f, .9f, 1.f);

	// Load assets
	theshader.tryload();
	if (!theshader.loaded) { stop("shader load failed"); }
	shader_skybox.tryload();
	if (!shader_skybox.loaded) { stop("shader_skybox load failed"); }

	camera.load();
	if (!camera.loaded()) { stop("camera load failed"); }
	skybox.load();
	if (!skybox.loaded()) { stop("skybox load failed"); }

	for (int i = 0; i < scene.nobjs; i++) {
		scene.objects[i]->load();
		if (!scene.objects[i]->loaded()) { stop(scene.objects[i]->tag + "load failed"); }
	}

	gameloop();

	stop("Game over");
}

void engine::gameloop()
{
	while (!isdown(input_esc)) {
		// End old frame, start new one
		glfwSwapBuffers(window.ptr);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glfwPollEvents();

		timer.t += timer.dt = (float)(glfwGetTime() - timer.t);

		cursor.x0 = cursor.x; cursor.y0 = cursor.y;
		glfwGetCursorPos(window.ptr, &cursor.x, &cursor.y);

		// Update scene
		skybox.update();
		camera.update();
		for (int i = 0; i < scene.nobjs; i++) {
			scene.objects[i]->update();
		}

		// Render scene
		skybox.render();
		camera.render();
		for (int i = 0; i < scene.nobjs; i++) {
			scene.objects[i]->render();
		}
	}
}

void engine::stop(std::string comment)
{
	printf("\n%s\n", comment.c_str());

	theshader.unload();
	shader_skybox.unload();
	
	// Unload scene
	skybox.unload();
	camera.unload();
	for (int i = 0; i < scene.nobjs; i++) {
		scene.objects[i]->unload();
	}

	glfwTerminate();
}
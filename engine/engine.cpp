/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "engine.h"

#include <iostream>
#include <thread>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Variables declared static in engine class namespace, but allocated/instantiated once in global memory
timer engine::timer;
input engine::input;
window engine::window;
shader engine::shader_pblinn("engine/shaders/vshader.glsl", "engine/shaders/fshader.glsl");
shader engine::shader_skybox("engine/shaders/vshader_skybox.glsl", "engine/shaders/fshader_skybox.glsl");

// Scene objects
scene engine::scene;
object& engine::sky = *(engine::scene.objects[0]);
camera& engine::cam = *(camera*)(engine::scene.objects[1]);

void engine::start()
{
	// GLFW, window, & GLEW
	if (glfwInit() != GL_TRUE) { stop("GLFW init failed"); }
	window.ptr = glfwCreateWindow(window.w, window.h, window.title.c_str(), NULL, NULL); //glfwGetPrimaryMonitor(), NULL
	if (nullptr == window.ptr) { stop("GLFW create window failed"); }
	glfwMakeContextCurrent(window.ptr);
	if (glewInit() != GLEW_OK) { stop("GLEW init failed"); }

	// Renderer
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(.45f, .45f, .9f, 1.f);

	// Input
	input.start();

	// Shaders
	if (!shader_pblinn.load()) stop("Shader load failed");
	if (!shader_skybox.load()) stop("Skybox shader load failed");

	// Scene
	for (int i = 0; i < scene.nobjs; i++)
		if (!scene.objects[i]->load())
			stop(scene.objects[i]->tag + " object load failed");

	gameloop();

	stop("Game over");
}

void engine::gameloop()
{
	while (!glfwWindowShouldClose(engine::window.ptr)) 
	{
		// Input from user		(per user)
		input.update();

		// Process scene		(predicted by users, corrected by server?)
		timer.t += timer.dt = (float)(glfwGetTime() - timer.t);
		for (int i = 0; i < scene.nobjs; i++)
			scene.objects[i]->update();
		scene.clean();			//(removes objects with .garbage == true, sometimes crashes)

		// Render sky and scene(per user - how to handle multiple povs?)
		glfwSwapBuffers(window.ptr);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shader_skybox.use();
		cam.uploadpov();
		sky.render();
		glClear(GL_DEPTH_BUFFER_BIT);
		
		shader_pblinn.use();
		cam.uploadpov();
		for (int i = 2; i < scene.nobjs; i++)
			scene.objects[i]->render();
	}
}

void engine::stop(std::string comment)
{
	printf("\n%s\n", comment.c_str());

	// assets.unload
	for (auto& pair : asset::assets)
		if (pair.second) pair.second->unload();
	asset::assets = {};
	
	// delete objects from scene
	for (int i = 0; i < scene.nobjs; i++) {
		delete scene.objects[i];
		scene.objects[i] = nullptr;
	}
	scene.nobjs = 0;

	glfwTerminate();

	std::this_thread::sleep_for(std::chrono::seconds(1));
}
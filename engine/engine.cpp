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
float engine::pi = glm::pi<float>();
timer engine::timer;

#define cllbck \
	if (action == GLFW_REPEAT) return; \
	engine::input.down[key] += engine::input.ddown[key] = action - engine::input.down[key];
void kbcllbck(GLFWwindow* ptr, int key, int scancode, int action, int mods) { cllbck }
void mscllbck(GLFWwindow* ptr, int key, int action, int mods) { cllbck }

void cursor::update() {
	double nx, ny;
	glfwGetCursorPos(engine::window.ptr, &nx, &ny);
	x += dx = (float)nx - x;
	y += dy = (float)ny - y;
}

input engine::input;
cursor engine::cursor;
window engine::window;
shader engine::shader_pblinn("engine/shaders/vshader.glsl", "engine/shaders/fshader.glsl");

// Scene objects
scene engine::scene;
skybox& engine::sky = *(skybox*)(engine::scene.objects[0]);
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

	// Input & cursor
	glfwSetKeyCallback(window.ptr, &kbcllbck);
	glfwSetMouseButtonCallback(window.ptr, &mscllbck);
	cursor.update();

	// Shader
	if (!shader_pblinn.load())
		stop("Shader load failed");
	shader_pblinn.use();
	
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
		// Input from user		(all users with different windows/cursors and input states?)
		input.ddown = {};
		glfwPollEvents();
		cursor.update();

		// Process scene		(by server? predicted by users?
		timer.t += timer.dt = (float)(glfwGetTime() - timer.t);
		for (int i = 0; i < scene.nobjs; i++)
			scene.objects[i]->update();
		scene.clean();

		// Output scene			(per user? all with different camera povs?)
		glfwSwapBuffers(window.ptr);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (int i = 0; i < scene.nobjs; i++)
			scene.objects[i]->render();
	}
}

void engine::stop(std::string comment)
{
	printf("\n%s\n", comment.c_str());

	// assets.unload
	for (auto& pair : asset::assets)
		if(pair.second) pair.second->unload();
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
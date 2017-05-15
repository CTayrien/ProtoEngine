#include "input.h"
#include "engine.h"

#define cllbck \
	if (action == GLFW_REPEAT) return; \
	engine::input.update(key, action);
void kbcllbck(GLFWwindow* ptr, int key, int scancode, int action, int mods) { cllbck }
void mscllbck(GLFWwindow* ptr, int key, int action, int mods) { cllbck }

input::input()
{
}

input::~input()
{
}

void input::update()
{
	ddown = {};
	glfwPollEvents();

	cursor.update();
}

void input::update(int key, int action)
{
	down[key] += ddown[key] = action - down[key];
}

void input::start()
{
	glfwSetKeyCallback(engine::window.ptr, &kbcllbck);
	glfwSetMouseButtonCallback(engine::window.ptr, &mscllbck);
	cursor.update();
}

void input::cursor::update()
{
	double nx, ny;
	glfwGetCursorPos(engine::window.ptr, &nx, &ny);
	x += dx = (float)nx - x;
	y += dy = (float)ny - y;
}
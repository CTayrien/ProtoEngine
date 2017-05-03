/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "window.h"
#include "engine.h"

window::window()
{
}

window::~window()
{
}

void window::start()
{
	if (glfwInit() != GL_TRUE)	return;

	ptr = glfwCreateWindow(w, h, title.c_str(), NULL, NULL); //glfwGetPrimaryMonitor(), NULL
	if (nullptr == ptr) return;
	glfwMakeContextCurrent(ptr);

	if (glewInit() != GLEW_OK) return;

	// Renderer basics
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(.45f, .45f, .9f, 1.f);
}

void window::stop()
{
	glfwTerminate();
}

void window::update()
{
	// Send color buffer to screen, clear new frame buffers
	glfwSwapBuffers(ptr);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Process queued changes to window and input
	glfwPollEvents();

	cursorx0 = cursorx;
	cursory0 = cursory;
	glfwGetCursorPos(ptr, &cursorx, &cursory);
	dx = cursorx - cursorx0;
	dy = cursory - cursory0;
}

void window::clampcursor()
{
	cursorx = glm::clamp(cursorx, (double)0, (double)w);
	cursory = glm::clamp(cursory, (double)0, (double)h);
	glfwSetCursorPos(ptr, cursorx, cursory);
}
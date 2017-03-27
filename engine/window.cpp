/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "window.h"

std::string window::title = "Proto Engine";

GLFWwindow* window::ptr = nullptr;

double window::cursorx;
double window::cursory;

int window::w = 1600;
int window::h = 900;

int window::halfw = window::w/2;
int window::halfh = window::h/2;

bool window::start()
{
	//ptr = glfwCreateWindow(w, h, title.c_str(), glfwGetPrimaryMonitor(), NULL);
	ptr = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	
	if (nullptr == ptr) return false;
	glfwMakeContextCurrent(ptr);

	return true;
}

void window::update()
{
	// Process queued changes to window and input
	glfwPollEvents();

	// Window data
	glfwGetCursorPos(ptr, &cursorx, &cursory);
}

void window::stop()
{
	glfwTerminate();
}
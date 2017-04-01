/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "window.h"

std::string window::title = "Proto Engine";

GLFWwindow* window::ptr = nullptr;

double window::cursorx;
double window::cursory;
double window::cursorx0;
double window::cursory0;
double window::dx;
double window::dy;

int window::w = 1200;
int window::h = 900;

int window::halfw = window::w/2;
int window::halfh = window::h/2;

bool window::start()
{
	ptr = glfwCreateWindow(w, h, title.c_str(), NULL, NULL); //glfwGetPrimaryMonitor(), NULL
	
	if (nullptr == ptr) return false;
	glfwMakeContextCurrent(ptr);

	return true;
}

void window::update()
{
	// Process queued changes to window and input
	glfwPollEvents();

	// Window data
	cursorx0 = cursorx;
	cursory0 = cursory;
	glfwGetCursorPos(ptr, &cursorx, &cursory);
	dx = cursorx - cursorx0;
	dy = cursory - cursory0;

	// If outside window, move cursor to center
	if (cursorx > w || cursorx < 0 || cursory > h || cursorx < 0) {
		glfwSetCursorPos(ptr, halfw, halfh);
		cursorx = cursorx0 = halfw;
		cursory = cursory0 = halfh;
		dx = dy = 0;
	}
}

void window::stop()
{
	glfwTerminate();
}
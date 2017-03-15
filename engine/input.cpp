/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "engine.h"

double input::cursorx;

double input::cursory;

bool input::start()
{
	return true;
}

void input::update()
{
	// Input data
	cursorx = window::cursorx / window::w;
	cursory = window::cursory / window::h;
}

bool input::isDown(int key)
{
	return GLFW_PRESS == glfwGetKey(window::ptr, key);
}

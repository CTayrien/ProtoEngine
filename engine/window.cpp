/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "window.h"
#include "engine.h"

window::window()
{
	w = 1200;
	h = 900;

	halfw = w / 2;
	halfh = h / 2;
}

window::~window()
{
}

void window::update()
{
	// Window data
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

	// move to center
	//if (cursorx > w || cursorx < 0 || cursory > h || cursorx < 0) {
	//	glfwSetCursorPos(ptr, halfw, halfh);
	//	cursorx = cursorx0 = halfw;
	//	cursory = cursory0 = halfh;
	//	dx = dy = 0;
	//}
}
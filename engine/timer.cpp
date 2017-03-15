/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "timer.h"

#include <GLFW\glfw3.h>

timer::timer()
{
}

timer::~timer()
{
}

void timer::start()
{
	//cur = clock();		//ctime
	t = 0;
	dt = 0;
	fps = 0;

	// Rel
	dtau = 0;
	tau = 0;
}

void timer::update()
{
	// ctime
	//prev = cur;
	//cur = clock();
	//dt = (cur - prev) / (float)CLOCKS_PER_SEC;
	//t += dt;
	//fps = 1.f / dt;	//approx immediate

	dt = static_cast<float>(glfwGetTime()) - t;
	t += dt;
	fps = 1 / dt;

	// Rel
	dtau = dt / g;
	tau += dtau;
}
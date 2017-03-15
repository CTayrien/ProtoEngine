/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class window
{
public:
	static std::string title;

	static GLFWwindow *ptr;

	static double cursorx, cursory;
	
	static int w, h;
	static int halfw, halfh;
	
	static bool start();

	static void update();

	static void stop();
};


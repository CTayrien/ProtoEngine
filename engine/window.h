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
	std::string title = "Proto Engine";

	GLFWwindow *ptr;

	double cursorx, cursory;
	double cursorx0, cursory0;
	double dx, dy;
	
	int w = 1200;
	int h = 900;
	int halfw = w / 2;
	int halfh = h / 2;
	float aspect;

	window();
	~window();

	void start();
	void stop();

	void update();

	void clampcursor();
};
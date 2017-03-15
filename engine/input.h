/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#define input_esc 256	//GLFW_KEY_ESC

class input
{
public:
	static double cursorx, cursory;
	
	static bool start();

	static void update();

	static bool isDown(int key);
};


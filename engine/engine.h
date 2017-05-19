/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include <gl\glew.h>
#include <GLFW\glfw3.h>

#include "object.h"
#include "camera.h"
#include "shader.h"
#include "scene.h"
#include "input.h"

/* prioritized to do:
    asset mngmnt: smart ptr asset mngmnt, factory?
    visuals: lighting & shadows, particle fx, 
    game-y stuff: scenes, save/load, 
    external stuff: imgui, nsight, 
	ai stuff: creatures & satellites, 
    collision stuff: collision system w/ struct, swept volume, 
    physics stuff: corrector (L or H?), quat moment tensor torque collision, fluids & softbody, relativity, 
    use assets: levels, sound, animation, spritesheet, 
    graphics: element array rendering, instanced rendering, render lists, 
    parallelization: multithreading, gpu physics, networking
*/

struct window {
	std::string title = "Proto Engine";
	int w = 1200, h = 900;
	GLFWwindow* ptr = nullptr;
};

struct timer { float t = 0, dt = 0; };

class engine
{
public:
	static window window;
	static timer timer;

	static input input;

	static shader shader_pblinn;
	static shader shader_skybox;

	static camera& cam;
	static object& sky;
	static scene scene;

	static void start();
	static void gameloop();
	static void stop(std::string comment);
};
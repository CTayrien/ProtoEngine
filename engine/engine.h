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

/* future cs & physics engine / scene development:
    interests: scenes, center on start-up, imgui, nsight, collision system w/ struct, lighting & shadows, particle fx, flocking (& docking?), fluids & softbody, 
	game engine: smart ptr asset mngmnt, save/load, levels, sound, animation, spritesheet, networking, 
	physics: quat moment tensor torque, collision manifold, swept volume, predictor-corrector (L or H?),
    graphics optimization: element array rendering, instanced rendering, render lists, 
    parallel: multithreading, gpu physics,
    adv physics: n-body, astrodynamics, relativity, electrodynamics, quantum, 
*/

struct window {
	std::string title = "Proto Engine";
	int w = 1200, h = 800;
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
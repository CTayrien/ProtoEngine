/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include <gl\glew.h>
#include <GLFW\glfw3.h>

#include "object.h"
#include "camera.h"
#include "skybox.h"
#include "shader.h"
#include "scene.h"
#include "input.h"

/* prioritized to do:
visuals: lighting & shadows, particle fx,
ai stuff: creatures
external stuff: imgui, nsight,  
physics stuff: quat & torque, predictor corrector, collider systems & manifolds, fluids & softbody, relativity
game-y stuff: scenes, levels, animation, sound, networking, save/load
graphic optimizations: element array rendering, instanced rendering, render lists
parallelization: multithreading, gpu physics
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

	// scene shaders - should be on scene, skybox or camera? skybox shader is on skybox - that is normal (most objects should have a ref to their shader, and does render manager uses them to prioritize render calls?)
	static shader shader_pblinn;
	
	static camera& cam;
	static skybox& sky;
	static scene scene;

	static void start();
	static void gameloop();
	static void stop(std::string comment);
};
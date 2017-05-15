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

struct window {
	std::string title = "Proto Engine";
	int w = 1200, h = 900;
	GLFWwindow* ptr = nullptr;
};

struct timer { float t = 0, dt = 0; };

// scene should store new'd pointers via spawn function
// they are erase-removed and deleted by the despawn func. when game exits, all are despawned, then resource maps are unloaded

class engine
{
public:
	static float pi;

	static input input;

	static window window;
	static timer timer;

	// scene shaders - should be on scene, skybox or camera? skybox shader is on skybox - that is normal (most objects should have a ref to their shader, and render manager uses them to prioritize render calls)
	static shader shader_pblinn;
	
	static camera& cam;
	static skybox& sky;
	static scene scene;

	static void start();
	static void gameloop();
	static void stop(std::string comment);
};
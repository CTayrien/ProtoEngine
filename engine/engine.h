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

#pragma region GLFW_INPUT_INTERFACE

#define input_esc	GLFW_KEY_ESCAPE
#define input_space GLFW_KEY_SPACE
#define input_enter GLFW_KEY_ENTER

#define input_ctrl		GLFW_KEY_LEFT_CONTROL
#define input_shift		GLFW_KEY_LEFT_SHIFT
#define input_alt		GLFW_KEY_LEFT_ALT

#define input_w		GLFW_KEY_W
#define input_a		GLFW_KEY_A
#define input_s		GLFW_KEY_S
#define input_d		GLFW_KEY_D

#define input_q		GLFW_KEY_Q
#define input_e		GLFW_KEY_E
#define input_r		GLFW_KEY_R
#define input_f		GLFW_KEY_F
#define input_z		GLFW_KEY_Z
#define input_x		GLFW_KEY_X
#define input_c		GLFW_KEY_C
#define input_v		GLFW_KEY_V

#define input_up	GLFW_KEY_UP
#define input_down	GLFW_KEY_DOWN
#define input_left	GLFW_KEY_LEFT
#define input_right GLFW_KEY_RIGHT

#define input_mouse_left	GLFW_MOUSE_BUTTON_LEFT
#define input_mouse_right	GLFW_MOUSE_BUTTON_RIGHT
#define input_mouse_middle	GLFW_MOUSE_BUTTON_MIDDLE

#define input_tilde GLFW_KEY_GRAVE_ACCENT
#define input_1		GLFW_KEY_1
#define input_2		GLFW_KEY_2
#define input_3		GLFW_KEY_3
#define input_4		GLFW_KEY_4
#define input_5		GLFW_KEY_5
#define input_6		GLFW_KEY_6
#define input_7		GLFW_KEY_7
#define input_8		GLFW_KEY_8
#define input_9		GLFW_KEY_9
#define input_0		GLFW_KEY_0

#pragma endregion

// input?

struct window {
	std::string title = "Proto Engine";
	int w = 1200, h = 900;
	GLFWwindow* ptr = nullptr;
};

struct cursor {
	double x, y, x0, y0;
};

struct timer {
	float t = 0, dt = 0;
};

struct scene {
	int nobjs;
	object* objects[256];
	void add(object* object) { 
		if (nobjs < 256)
			objects[nobjs++] = object;
	}
};

class engine
{
public:
	static float pi;

	//input
	// to do: enable registering a single keypress: tracking what is down vs what was down with 2 maps, update them each frame with input callbacks
	static bool isdown(int key);

	static window window;
	static cursor cursor;
	static timer timer;

	// scene shaders
	static shader shader_pblinn;
	static shader shader_skybox;
	
	// scene objects
	static camera camera;
	static skybox skybox;
	static scene scene;

	static void start();
	static void gameloop();
	static void stop(std::string comment);
};
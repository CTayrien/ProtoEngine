/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include "window.h"
#include "object.h"			// includes model, texture
#include "timer.h"
#include "camera.h"
#include "skybox.h"
#include "shader.h"

#pragma region GLFW_INPUT_INTERFACE

#define input_esc	GLFW_KEY_ESCAPE
#define input_space GLFW_KEY_SPACE
#define input_enter GLFW_KEY_ENTER

#define input_ctrl_left		GLFW_KEY_LEFT_CONTROL
#define input_shift_left	GLFW_KEY_LEFT_SHIFT
#define input_alt_left		GLFW_KEY_LEFT_ALT

#define input_ctrl_right	GLFW_KEY_RIGHT_CONTROL
#define input_shift_right	GLFW_KEY_RIGHT_SHIFT
#define input_alt_right		GLFW_KEY_RIGHT_ALT

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

class engine
{
private:

public:
	static float pi;

	static window window;
	static timer time;

	static camera cam;
	static skybox skybox;

	static shader theshader;
	static shader shader_skybox;

	// to do: enable registering a single keypress: tracking what is down vs what was down with 2 maps, update them each frame with input callbacks
	static bool inputdown(int key);

	static bool start();
	static void update();
	static void stop();
};
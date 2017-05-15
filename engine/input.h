#pragma once
#include <map>

#pragma region GLFW_INPUT_INTERFACE

#define input_tilde GLFW_KEY_GRAVE_ACCENT
#define input_esc	GLFW_KEY_ESCAPE
#define input_space GLFW_KEY_SPACE
#define input_enter GLFW_KEY_ENTER
#define input_ctrl	GLFW_KEY_LEFT_CONTROL
#define input_shift	GLFW_KEY_LEFT_SHIFT
#define input_alt	GLFW_KEY_LEFT_ALT
#define input_up	GLFW_KEY_UP
#define input_down	GLFW_KEY_DOWN
#define input_left	GLFW_KEY_LEFT
#define input_right GLFW_KEY_RIGHT

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

#define input_mouse_left	GLFW_MOUSE_BUTTON_LEFT
#define input_mouse_right	GLFW_MOUSE_BUTTON_RIGHT
#define input_mouse_middle	GLFW_MOUSE_BUTTON_MIDDLE

#pragma endregion


class input
{
public:
	std::map<int, int> down, ddown;
	struct cursor {
		float x, y, dx, dy;
		void update();
	} cursor;

	input();
	~input();

	void update();
	void update(int key, int action);
	void start();
};
/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include "window.h"
#include "input.h"
#include "object.h"			// includes model, texture
#include "timer.h"
#include "camera.h"
#include "light.h"
#include "skybox.h"
#include "shader.h"
#include "material.h"

class engine
{
private:

public:
	static float pi;

	static timer time;
	
	static camera cam;

	static light light;

	static skybox skybox;

	static shader theshader;
	static shader shader_skybox;
	static material thematerial;

	static window window;

	static bool start();
	static void update();
	static void stop();
};
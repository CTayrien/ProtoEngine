/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include "window.h"
#include "input.h"
#include "renderer.h"		// includes material, shader
#include "object.h"			// includes model, texture
#include "timer.h"
#include "camera.h"
#include "light.h"
#include "skybox.h"

class engine
{
private:

public:
	static timer time;
	
	static camera cam;

	static light light;

	static skybox skybox;

	static bool start();
	static void update();
	static void stop();
};
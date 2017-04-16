/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#pragma once

#include "shader.h"
#include "material.h"

class renderer
{
private:
	static shader theshader;
	static shader shader_skybox;

public:	
	static material thematerial;

	static bool start();

	static void update();
	
	static void stop();
};
/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "material.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

material::material()
{
}

material::material(float amb, float diff, float spec, float specpow)
{
	ambDifSpec[0] = amb;
	ambDifSpec[1] = diff;
	ambDifSpec[2] = spec;
	ambDifSpec[3] = specpow;
}


material::~material()
{
}

void material::use()
{
	glUniform4fv(id, 1, ambDifSpec);
}

/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "Globe.h"
#include "engine.h"

Globe::Globe()
{
	this->tex = texture({ "objects/planet/earth.png" });
	this->mod = model({ "engine/models/sphere.dat" });
	mtl.rgba.a = .5;
}

Globe::~Globe()
{

}

void Globe::script()
{
}

void Globe::render()
{
	// Render interior of back side
	glCullFace(GL_FRONT);
	object::render();
	glCullFace(GL_BACK);

	// Render exterior of front side
	object::render();
}

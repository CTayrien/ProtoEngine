/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "Globe.h"

Globe::Globe()
{
	this->tex = new texture("objects/planet/earth.png");
	this->mod = new model("engine/models/sphere2.dat");
}

Globe::~Globe()
{
	delete tex;
	delete mod;
}

void Globe::script()
{
	
}
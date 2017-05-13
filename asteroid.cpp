/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "asteroid.h"

asteroid::asteroid()
{
	tag = "asteroid";
	mod = model({ "engine/models/sphere.dat" });
	tex = texture({ "engine/textures/brown.png" });
	tform.loc.y = 20;
	tform.vel.y = -20;
}

asteroid::~asteroid()
{
}

void asteroid::script()
{
}
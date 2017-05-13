/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "enemycraft.h"

enemycraft::enemycraft()
{
	tag = "enemy craft";
	mod = model({ "engine/models/tet.dat" });
	tex = texture({ "engine/textures/red.png" });
	tform.loc.y = 20;
	tform.vel.y = -20;
}

enemycraft::~enemycraft()
{
}

void enemycraft::script()
{
}
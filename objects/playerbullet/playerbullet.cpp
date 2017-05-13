/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "playerbullet.h"
#include "engine.h"

playerbullet::playerbullet()
{
	tag = "bullet";
	mod = model({ "engine/models/box.dat" });
	tex = texture({ "engine/textures/white.png" });
	tform.scale = { .05, .3, .05 };
	tform.vel.y = 70;
}

playerbullet::~playerbullet()
{
}

void playerbullet::script()
{
	lifetime += engine::timer.dt;
	if (lifetime > 1) garbage = true;
}
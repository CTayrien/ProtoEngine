/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "playercraft.h"
#include "engine\engine.h"


playercraft::playercraft()
{
	tag = "player";
	mod = model({ "engine/models/tet.dat" });
	tex = texture({ "engine/textures/yellow.png" });
}


playercraft::~playercraft()
{
}

void playercraft::script()
{
	// Drag - should be on tform?
	glm::vec3 d = tform.vel;
	if (d != glm::vec3()) d = glm::normalize(d);
	float x = glm::length(tform.vel);
	float a = 1, b = 1, c = 1;
	tform.force -= d * (a * x * x + b * x + c);

	// Toggle control (ball vs debug cam)
	if (engine::cam.isdebug) return;

	// Move
	float power = 1000;
	glm::vec3 md;
	if (engine::input.down[input_w]) md.y++;
	if (engine::input.down[input_a]) md.x--;
	if (engine::input.down[input_s]) md.y--;
	if (engine::input.down[input_d]) md.x++;
	if (md != glm::vec3()) md = glm::normalize(md);
	tform.force += md * power;

	// Shoot
	if (engine::input.ddown[input_mouse_left] == 1) {	
		engine::scene.spawn(new playerbullet);
		engine::scene.back()->tform.loc = tform.loc;
	}
}
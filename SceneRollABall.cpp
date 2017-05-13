/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include <ctime>

#include "engine\engine.h"

#include "rollaball.h"
#include "collectible.h"

void spawnitems(rollaball* player , int n)
{
	srand(time(0));

	for (int i = 0; i < 10; i++) {
		engine::scene.spawn(new collectible);
		collectible& c = *(collectible*)engine::scene.back();
		c.player = player;
		c.tform.loc.x = (float)rand() / (float)RAND_MAX * 20 - 10;
		c.tform.loc.y = (float)rand() / (float)RAND_MAX * 20 - 10;
	}
}

int main()
{
	// Background
	engine::scene.spawn(new object);
	object& background = *engine::scene.back();
	background.tag = "background";
	background.mod = model({ "engine/models/quad.dat" });
	background.tex = texture({ "engine/textures/white.png" });
	background.tform.scale = { 20, 20, 1 };
	background.tform.loc.z = -2;

	// Player
	engine::scene.spawn(new rollaball);
	rollaball& player = *(rollaball*)engine::scene.back();

	// Collectibles
	spawnitems(&player, 10);

	engine::cam.tform.loc.z = 16;
	engine::cam.setdebug(false);

	engine::start();

	return 0;
}
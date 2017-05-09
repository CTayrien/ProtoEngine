/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include <ctime>

#include "engine\engine.h"

#include "rollaball.h"
#include "collectible.h"

void spawnitems(const collectible& prefab, collectible* collectibles, int n) {
	for (int i = 0; i < 10; i++) {
		collectibles[i] = prefab;
		collectibles[i].tform.loc.x = (float)rand() / (float)RAND_MAX * 20 - 10;
		collectibles[i].tform.loc.y = (float)rand() / (float)RAND_MAX * 20 - 10;
		engine::scene.add(&collectibles[i]);
	}
}

int main()
{
	srand(time(0));

	model models[2] = {
		"engine/models/sphere.dat",
		"engine/models/box.dat" };

	texture textures[6] = {
		"engine/textures/white.png",
		"engine/textures/black.png",
		"engine/textures/red.png",
		"engine/textures/green.png",
		"engine/textures/blue.png",
		"engine/textures/earth.png"
	};

	object background;
	background.mod = &models[1];
	background.tex = &textures[0];
	background.tform.scale = { 20, 20, 1 };
	background.tform.loc.z = -2;
	engine::scene.add(&background);

	rollaball player;
	player.mod = &models[0];
	player.tex = &textures[5];
	engine::scene.add(&player);

	collectible prefab;
	prefab.mod = &models[1];
	prefab.tex = &textures[3];
	prefab.tform.scale = { .1, .1, .1 };
	prefab.player = &player;
	prefab.tform.rotvel = { 1,1,1 };

	collectible collectibles[10];
	spawnitems(prefab, collectibles, 10);

	engine::camera.tform.loc.z = 16;
	engine::camera.setdebug(false);

	engine::start();

	return 0;
}
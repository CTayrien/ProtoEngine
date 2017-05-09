/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/

#include "engine\engine.h"

#include "rollaball.h"
#include "collectible.h"

int main()
{
	srand(0);

	model models[2] = {"engine/models/sphere.dat","engine/models/box.dat"};
	texture textures[1] = { "engine/textures/white.png" };

	collectible collectibles[10];
	for (int i = 0; i < 10; i++) {
		collectibles[i].mod = &models[1];
		collectibles[i].tex = &textures[0];
		collectibles[i].tform.scale = { .1, .1, .1 };
		collectibles[i].tform.loc = glm::vec3(
			(float)rand() / (float)RAND_MAX * 20 - 10,
			0,//(float)rand() / (float)RAND_MAX * 20 - 10,
			(float)rand() / (float)RAND_MAX * 20 - 10
		);
		engine::scene.add(&collectibles[i]);
	}

	rollaball player;
	player.mod = &models[0];
	player.tex = &textures[0];
	player.collectibles = collectibles;
	player.ncollectibles = 10;
	engine::scene.add(&player);

	engine::camera.tform.loc = { 0, 10, 0 };
	engine::camera.tform.rot = { 0, -engine::pi/2, 0 };
	engine::camera.setdebug(false);

	engine::start();

	return 0;
}
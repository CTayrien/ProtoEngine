/* Proto Engine : free open-source educational prototype game engine for prototyping simple games.
Copyright(C) 2017  Cyprian Tayrien, Interactive Games and Media, Rochester Institute of Technology
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "playarea.h"
#include "engine.h"

playarea::playarea()
{
	tag = "play area";
	tform.scale = { 20, 20, 20 };
}

playarea::~playarea()
{
}

void playarea::render()
{
}

bool playarea::load()
{
	return true;
}

void playarea::script()
{
	// lerp player to clamp

	//for (int i = 0; i < player->nbullets; i++) {		//box-sphere failed for no reason?
	//	if (player->bullets[i].isactive && !collides<SPHERE, SPHERE>(player->bullets[i])) {
	//		player->bullets[i].isactive = false;
	//		engine::scene.remove(&player->bullets[i]);
	//	}
	//}
	//
	//for (int i = 0; i < nasteroids; i++) {
	//	if (asteroids[i].isactive && !collides<BOX, SPHERE>(asteroids[i])) {
	//		asteroids[i].isactive = false;
	//		engine::scene.remove(&asteroids[i]);
	//	}
	//}
	//
	//for (int i = 0; i < nenemies; i++) {
	//	if (enemies[i].isactive && !collides<BOX, SPHERE>(enemies[i])) {
	//		enemies[i].isactive = false;
	//		engine::scene.remove(&enemies[i]);
	//	}
	//}
}
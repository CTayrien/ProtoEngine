#include "playarea.h"
#include "engine\engine.h"


playarea::playarea()
{
}


playarea::~playarea()
{
}

void playarea::script()
{
	// lerp player to clamp

	for (int i = 0; i < player->nbullets; i++) {
		if (player->bullets[i].isactive && !collides<BOX, SPHERE>(player->bullets[i])) {
			player->bullets[i].isactive = false;
			engine::scene.remove(&player->bullets[i]);
		}
	}

	for (int i = 0; i < nasteroids; i++) {
		if (asteroids[i].isactive && !collides<BOX, SPHERE>(asteroids[i])) {
			asteroids[i].isactive = false;
			engine::scene.remove(&asteroids[i]);
		}
	}

	for (int i = 0; i < nenemies; i++) {
		if (enemies[i].isactive && !collides<BOX, SPHERE>(enemies[i])) {
			enemies[i].isactive = false;
			engine::scene.remove(&enemies[i]);
		}
	}
}
